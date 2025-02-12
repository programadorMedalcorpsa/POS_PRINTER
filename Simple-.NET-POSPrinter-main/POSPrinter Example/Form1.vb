Imports System.Drawing.Printing
Imports ZXing
Imports ZXing.Common

Public Class Form1

    Dim selectedPrinter As PrinterSettings

    Private Sub SelectPrinter_Click(sender As Object, e As EventArgs) Handles btnSelectPrinter.Click

        ' Show PrintDialog1 so the user can select the printer
        Dim selection As DialogResult = PrintDialog1.ShowDialog()

        If selection = DialogResult.OK Then
            selectedPrinter = PrintDialog1.PrinterSettings()
            Label1.Visible = True
            Label2.Visible = True
            Label2.Text = selectedPrinter.PrinterName
        End If

    End Sub

    Private Sub btnPrintTest_Click(sender As Object, e As EventArgs) Handles btnPrintTest.Click
        Dim pd As New PrintDocument()
        pd.PrinterSettings = selectedPrinter
        AddHandler pd.PrintPage, AddressOf printTestLabel
        pd.Print()
    End Sub

    Private Sub printTestLabel(sender As Object, e As PrintPageEventArgs)

        'Setup the printer
        Dim myPrinter As New POSPrinter(e) With {
                .Font = New Font("Arial", 12, FontStyle.Bold),  'Specify a Font
                .Brush = New SolidBrush(Color.Black)            'Specify a Color (Usually only Black is available)
            }

        'Print "POSPrinter" centered 
        myPrinter.PrintTextLn("POSPrinter", "center")           'PrintTextLn() prints the text and then goes to a new line

        'Print a divider
        myPrinter.PrintHLine()                                  'PrintHLine() prints an horizontal line same width as page

        'Change font from Bold to Regular
        myPrinter.Font = New Font("Arial", 12, FontStyle.Regular)

        'Print "Version: " aligned right
        myPrinter.PrintText("Version: ")                        'PrintText() prints the text without going to new line
        myPrinter.PrintTextLn("1.0.0")

        myPrinter.PrintTextLn("Made by:")
        myPrinter.PrintTextLn("Timothy Franceschi", "center")

        'Create some space
        myPrinter.EmptyLine()                                   'EmptyLine() leave an extra line as spacing

        'Setup barcode options
        Dim barcodeOptions As New EncodingOptions With {
            .Width = 279,
            .Height = 93,
            .NoPadding = True,
            .Margin = 0
        }

        'Setup barcode value
        Dim barcodeText As String = "12345"

        'Setup barcode type
        Dim barcodeType As BarcodeFormat = BarcodeFormat.CODE_128

        'Print the barcode
        myPrinter.PrintBarcode(barcodeText, barcodeOptions, barcodeType)

    End Sub

End Class
