Public Class frmTraceItems




    Private Sub btnCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCancel.Click
        Me.Hide()
    End Sub

    Private Sub frmTraceItems_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        clbList.Items.Clear()
        Dim iItem As Integer
        'populate
        If Not IsNothing(frmMain.strTraceItems) Then

            For iItem = LBound(frmMain.strTraceItems) To UBound(frmMain.strTraceItems)
                clbList.Items.Add(frmMain.strTraceItems(iItem))
            Next
        End If

        'Set
        For iItem = 0 To clbList.Items.Count - 1
            clbList.SetItemChecked(iItem, GetSetting("TraceProgram", "TraceItems", clbList.GetItemText(iItem), True))
        Next

    End Sub

    Private Sub clbList_ItemCheck(ByVal sender As Object, ByVal e As System.Windows.Forms.ItemCheckEventArgs) Handles clbList.ItemCheck
        SaveSetting("TraceProgram", "TraceItems", clbList.GetItemText(e.Index), clbList.GetItemChecked(e.Index))
    End Sub

    Private Sub clbList_SelectedIndexChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles clbList.SelectedIndexChanged

    End Sub
End Class