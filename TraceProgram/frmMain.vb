Imports System.Net.Sockets
Imports System.Text
Public Class frmMain

    Enum eContent
        Trace
        Details
        Unknown
    End Enum

    Private Sub frmMain_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        InitList()
        Dim tThread As Threading.Thread = New System.Threading.Thread(AddressOf Listen)
        tThread.Start()
    End Sub

    Private Sub Listen()
        While (True)
            Dim sListener As New TcpListener(55555)
            Dim clientSocket As TcpClient
            sListener.Start()

            clientSocket = sListener.AcceptTcpClient()
            Dim nsStream As NetworkStream = clientSocket.GetStream()
            Dim bReceiveBuffer(0) As Byte
            Dim Trace As String = String.Empty
            Dim Details As String = String.Empty
            Dim oMode As eContent = eContent.Unknown

            Dim iBytesRead As Integer
            Do
                Try
                    iBytesRead = nsStream.Read(bReceiveBuffer, 0, 1)
                    Select Case bReceiveBuffer(0)
                        Case 0
                            Debug.Print("Start Trace")
                            oMode = eContent.Trace
                            Exit Select
                        Case 1
                            Debug.Print("Start Details")
                            oMode = eContent.Details
                            Exit Select
                        Case 2
                            Debug.Print("Flush")
                            oMode = eContent.Unknown
                            ListViewAddItem(Trace, Details)
                            NotifyIcon1.ShowBalloonTip(1000, "Info", System.Text.Encoding.ASCII.GetString(bReceiveBuffer), ToolTipIcon.None)
                            Trace = String.Empty
                            Details = String.Empty
                            Exit Select
                        Case Else
                            Debug.Print(Chr(bReceiveBuffer(0)))
                            Select Case oMode
                                Case eContent.Trace
                                    Trace += Chr(bReceiveBuffer(0))
                                    Exit Select
                                Case eContent.Details
                                    Details += Chr(bReceiveBuffer(0))
                                    Exit Select
                            End Select
                    End Select


                Catch ex As Exception

                End Try

                Application.DoEvents()
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
            lvTraces.Items.AddRange(New ListViewItem() {lvi})
            lvTraces.EnsureVisible(lvTraces.Items.Count - 1)
            lvTraces.ResumeLayout()
            If (Trace = "INFO") Then
                NotifyIcon1.ShowBalloonTip(1000, Trace, Details, ToolTipIcon.None)
            End If
        End If
    End Sub
 

    Private Sub Form1_Resize(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Resize

    End Sub

    Private Sub Form1_ResizeEnd(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.ResizeEnd
        SizeList()
    End Sub
End Class
