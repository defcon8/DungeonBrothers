Public Class frmTraceItems
    Private Sub btnCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCancel.Click
        Me.Close()
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
            clbList.SetItemChecked(iItem, frmMain.blTraceItems(iItem))
        Next

    End Sub

    Private Sub btnOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnOK.Click
        SaveTraceOptions()
        Me.Close()
    End Sub

    Sub SaveTraceOptions()
        For iItem = 0 To clbList.Items.Count - 1
            Debug.Print(clbList.Items(iItem) & vbTab & clbList.GetItemChecked(iItem))
            frmMain.blTraceItems(iItem) = clbList.GetItemCheckState(iItem)
            SaveSetting("TraceProgram", "TraceItems", clbList.Items(iItem), clbList.GetItemCheckState(iItem))
        Next
    End Sub

    Private Sub btnCheckAll_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnCheckAll.Click
        For iItem = 0 To clbList.Items.Count - 1
            clbList.SetItemCheckState(iItem, CheckState.Checked)
        Next
    End Sub

    Private Sub btnUncheckAll_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnUncheckAll.Click
        For iItem = 0 To clbList.Items.Count - 1
            clbList.SetItemCheckState(iItem, CheckState.Unchecked)
        Next
    End Sub
End Class