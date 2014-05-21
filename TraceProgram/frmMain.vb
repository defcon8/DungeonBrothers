Imports System.Net.Sockets
Imports System.Text
Public Class frmMain

    Dim tThread As Threading.Thread
    Shared blExiting As Boolean
    Shared clientSocket As TcpClient
    Shared sListener As New TcpListener(55555)
    Public Shared strTraceItems() As String
    Public Shared blTraceItems() As Boolean

    Enum eContent
        Trace
        Details
        TraceItems
        Unknown
    End Enum

    Private Sub frmMain_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        blExiting = True
        sListener.Stop()
        tThread.Abort()
    End Sub

    Private Sub frmMain_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        Me.DoubleBuffered = True
        InitList()
        tThread = New System.Threading.Thread(AddressOf Listen)
        tThread.IsBackground = True
        tThread.Start()
    End Sub

    Private Sub Listen()
        While (Not blExiting)

            Try
                sListener.Start()
            Catch ex As Exception
                MsgBox("Failed to start listener socket (port 55555 in use?).")
                Application.Exit()
            End Try

            clientSocket = sListener.AcceptTcpClient()
            Dim nsStream As NetworkStream = clientSocket.GetStream()
            nsStream.ReadTimeout = 1000
            Dim bReceiveBuffer(0) As Byte
            Dim Trace As String = String.Empty
            Dim TraceItems As String = String.Empty
            Dim Details As String = String.Empty
            Dim oMode As eContent = eContent.Unknown

            Dim iBytesRead As Integer
            Do
                Try
                    iBytesRead = nsStream.Read(bReceiveBuffer, 0, 1)
                    If iBytesRead > 0 Then
                        Debug.Print(bReceiveBuffer(0) & Chr(bReceiveBuffer(0)))
                        Select Case bReceiveBuffer(0)
                            Case 0
                                Trace = String.Empty
                                oMode = eContent.Trace
                                Exit Select
                            Case 1
                                Details = String.Empty
                                oMode = eContent.Details
                                Exit Select
                            Case 2
                                oMode = eContent.Unknown
                                If IsTraceEnabled(Trace) Then
                                    ListViewAddItem(Trace, Details)
                                    'NotifyIcon1.ShowBalloonTip(1000, "Info", System.Text.Encoding.ASCII.GetString(bReceiveBuffer), ToolTipIcon.None)
                                End If
                                Trace = String.Empty
                                Details = String.Empty
                                Exit Select
                            Case 3
                                Debug.Print("Start Trace Items")
                                oMode = eContent.TraceItems
                                TraceItems = String.Empty
                                Exit Select
                            Case 4
                                Debug.Print("End Trace Items")
                                Dim strSplitItems() As String = TraceItems.Split(",")
                                ReDim strTraceItems(UBound(strSplitItems))
                                ReDim blTraceItems(UBound(strSplitItems))
                                strTraceItems = strSplitItems
                                GetTraceItemsState()
                                Exit Select
                            Case Else
                                Select Case oMode
                                    Case eContent.Trace
                                        Trace += Chr(bReceiveBuffer(0))
                                        Exit Select
                                    Case eContent.Details
                                        Details += Chr(bReceiveBuffer(0))
                                        Exit Select
                                    Case eContent.TraceItems
                                        TraceItems += Chr(bReceiveBuffer(0))
                                        Exit Select
                                End Select
                        End Select
                    End If
                Catch ex As Exception

                End Try
            Loop Until (iBytesRead = 0 Or clientSocket.Connected = False)
            clientSocket.Close()
            sListener.Stop()
        End While
    End Sub


    Private Sub InitList()
        lvTraces.View = View.Details
        lvTraces.Columns.Add("Time")
        lvTraces.Columns.Add("Trace")
        lvTraces.Columns.Add("Details")
        SizeList()
    End Sub

    Private Sub SizeList()
        lvTraces.Columns(0).Width = 100
        lvTraces.Columns(1).Width = 100
        lvTraces.Columns(2).Width = lvTraces.Width - (lvTraces.Columns(0).Width + lvTraces.Columns(1).Width + 40)
    End Sub

    Private Delegate Sub ListViewAddItem_delegate(ByVal Trace As String, ByVal Details As String)
    Private Sub ListViewAddItem(ByVal Trace As String, ByVal Details As String)
        If Me.lvTraces.InvokeRequired Then
            Dim d As New ListViewAddItem_delegate(AddressOf ListViewAddItem)
            Me.lvTraces.BeginInvoke(d, {Trace, Details})
        Else
            lvTraces.SuspendLayout()
            Dim lvi As New ListViewItem(Now.ToString)
            lvi.SubItems.Add(Trace)
            lvi.SubItems.Add(Details)
            lvTraces.Items.Insert(0, lvi)
            'lvTraces.EnsureVisible(lvTraces.Items.Count - 1)
            lvTraces.ResumeLayout()
            'NotifyIcon1.ShowBalloonTip(750, Trace, Details, ToolTipIcon.None)
        End If

        If (lvTraces.Items.Count > 20) Then
            lvTraces.Items.RemoveAt(lvTraces.Items.Count - 1)
        End If

    End Sub

    Private Sub Form1_ResizeEnd(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.ResizeEnd
        SizeList()
    End Sub

    Private Sub ExitToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ExitToolStripMenuItem.Click
        Application.Exit()
    End Sub

    Private Sub btnTraceItems_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnTraceItems.Click
        frmTraceItems.Show()
    End Sub

    Private Sub GetTraceItemsState()
        Dim iItem As Integer
        For iItem = LBound(strTraceItems) To UBound(strTraceItems)
            blTraceItems(iItem) = GetSetting("TraceProgram", "TraceItems", strTraceItems(iItem), False)
        Next
    End Sub

    Private Function IsTraceEnabled(ByRef strTrace As String) As Boolean
        Dim iItem As Integer
        Dim blResult As Boolean = False
        For iItem = LBound(strTraceItems) To UBound(strTraceItems)
            If strTraceItems(iItem) = strTrace Then
                blResult = blTraceItems(iItem)
            End If
        Next
        Return blResult
    End Function

    Private Sub ClearToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ClearToolStripMenuItem.Click
        lvTraces.Clear()
    End Sub
End Class
