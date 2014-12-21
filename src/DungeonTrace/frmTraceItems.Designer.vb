<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmTraceItems
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.clbList = New System.Windows.Forms.CheckedListBox()
        Me.btnCancel = New System.Windows.Forms.Button()
        Me.btnOK = New System.Windows.Forms.Button()
        Me.btnCheckAll = New System.Windows.Forms.Button()
        Me.btnUncheckAll = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'clbList
        '
        Me.clbList.FormattingEnabled = True
        Me.clbList.Location = New System.Drawing.Point(12, 37)
        Me.clbList.Name = "clbList"
        Me.clbList.Size = New System.Drawing.Size(327, 544)
        Me.clbList.TabIndex = 0
        '
        'btnCancel
        '
        Me.btnCancel.Location = New System.Drawing.Point(250, 587)
        Me.btnCancel.Name = "btnCancel"
        Me.btnCancel.Size = New System.Drawing.Size(89, 26)
        Me.btnCancel.TabIndex = 1
        Me.btnCancel.Text = "Cancel"
        Me.btnCancel.UseVisualStyleBackColor = True
        '
        'btnOK
        '
        Me.btnOK.Location = New System.Drawing.Point(155, 587)
        Me.btnOK.Name = "btnOK"
        Me.btnOK.Size = New System.Drawing.Size(89, 26)
        Me.btnOK.TabIndex = 2
        Me.btnOK.Text = "OK"
        Me.btnOK.UseVisualStyleBackColor = True
        '
        'btnCheckAll
        '
        Me.btnCheckAll.Location = New System.Drawing.Point(12, 9)
        Me.btnCheckAll.Name = "btnCheckAll"
        Me.btnCheckAll.Size = New System.Drawing.Size(85, 22)
        Me.btnCheckAll.TabIndex = 3
        Me.btnCheckAll.Text = "Check All"
        Me.btnCheckAll.UseVisualStyleBackColor = True
        '
        'btnUncheckAll
        '
        Me.btnUncheckAll.Location = New System.Drawing.Point(103, 9)
        Me.btnUncheckAll.Name = "btnUncheckAll"
        Me.btnUncheckAll.Size = New System.Drawing.Size(85, 22)
        Me.btnUncheckAll.TabIndex = 4
        Me.btnUncheckAll.Text = "Uncheck All"
        Me.btnUncheckAll.UseVisualStyleBackColor = True
        '
        'frmTraceItems
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(352, 622)
        Me.Controls.Add(Me.btnUncheckAll)
        Me.Controls.Add(Me.btnCheckAll)
        Me.Controls.Add(Me.btnOK)
        Me.Controls.Add(Me.btnCancel)
        Me.Controls.Add(Me.clbList)
        Me.DoubleBuffered = True
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Name = "frmTraceItems"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Trace items"
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents clbList As System.Windows.Forms.CheckedListBox
    Friend WithEvents btnCancel As System.Windows.Forms.Button
    Friend WithEvents btnOK As System.Windows.Forms.Button
    Friend WithEvents btnCheckAll As System.Windows.Forms.Button
    Friend WithEvents btnUncheckAll As System.Windows.Forms.Button
End Class
