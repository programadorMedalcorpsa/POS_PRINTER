<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()>
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
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.btnSelectPrinter = New System.Windows.Forms.Button()
        Me.btnPrintTest = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.PrintDialog1 = New System.Windows.Forms.PrintDialog()
        Me.SuspendLayout()
        '
        'btnSelectPrinter
        '
        Me.btnSelectPrinter.Location = New System.Drawing.Point(12, 12)
        Me.btnSelectPrinter.Name = "btnSelectPrinter"
        Me.btnSelectPrinter.Size = New System.Drawing.Size(232, 85)
        Me.btnSelectPrinter.TabIndex = 0
        Me.btnSelectPrinter.Text = "Select printer"
        Me.btnSelectPrinter.UseVisualStyleBackColor = True
        '
        'btnPrintTest
        '
        Me.btnPrintTest.Location = New System.Drawing.Point(12, 103)
        Me.btnPrintTest.Name = "btnPrintTest"
        Me.btnPrintTest.Size = New System.Drawing.Size(232, 85)
        Me.btnPrintTest.TabIndex = 1
        Me.btnPrintTest.Text = "Print test"
        Me.btnPrintTest.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Segoe UI", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point)
        Me.Label1.Location = New System.Drawing.Point(264, 23)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(90, 28)
        Me.Label1.TabIndex = 2
        Me.Label1.Text = "Selected:"
        Me.Label1.Visible = False
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("Segoe UI", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point)
        Me.Label2.Location = New System.Drawing.Point(264, 51)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(95, 28)
        Me.Label2.TabIndex = 3
        Me.Label2.Text = "PRINTER"
        Me.Label2.Visible = False
        '
        'PrintDialog1
        '
        Me.PrintDialog1.UseEXDialog = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 20.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(487, 203)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.btnPrintTest)
        Me.Controls.Add(Me.btnSelectPrinter)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Name = "Form1"
        Me.Text = "POSPrinter Example"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents btnSelectPrinter As Button
    Friend WithEvents btnPrintTest As Button
    Friend WithEvents Label1 As Label
    Friend WithEvents Label2 As Label
    Friend WithEvents PrintDialog1 As PrintDialog
End Class
