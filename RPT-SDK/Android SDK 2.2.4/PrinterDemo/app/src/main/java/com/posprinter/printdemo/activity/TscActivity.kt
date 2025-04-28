package com.posprinter.printdemo.activity

import android.content.Intent
import android.graphics.Bitmap
import android.os.Bundle
import android.provider.MediaStore
import androidx.appcompat.app.AppCompatActivity
import com.posprinter.printdemo.App
import com.posprinter.printdemo.databinding.ActivityTscBinding
import net.posprinter.TSCConst
import net.posprinter.TSCPrinter

class TscActivity : AppCompatActivity() {
    private val printer = TSCPrinter(App.get().curConnect)
    private lateinit var bind: ActivityTscBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        bind = ActivityTscBinding.inflate(layoutInflater)
        setContentView(bind.root)
        initListener()
    }

    private fun initListener() {
        bind.content.setOnClickListener {
            printContent()
        }
        bind.tsctext.setOnClickListener {
            printText()
        }
        bind.tscbarcode.setOnClickListener {
            printBarcode()
        }
        bind.tscpic.setOnClickListener {
            printPic()
        }
    }

    private fun printPic() {
        val intent = Intent(Intent.ACTION_GET_CONTENT)
        intent.addCategory(Intent.CATEGORY_OPENABLE)
        intent.type = "image/*"
        startActivityForResult(intent, 0)
    }

    /*
    print the text ,line and barcode
     */
    private fun printContent() {
        printer.sizeMm(60.0, 30.0)
            .gapInch(0.0, 0.0)
            .offsetInch(0.0)
            .speed(5.0)
            .density(10)
            .direction(TSCConst.DIRECTION_FORWARD)
            .reference(20, 0)
            .cls()
            .box(6, 6, 378, 229, 5)
            .box(16, 16, 360, 209, 5)
            .barcode(30, 30, TSCConst.CODE_TYPE_93, 100, TSCConst.READABLE_LEFT, TSCConst.ROTATION_0, 2, 2, "ABCDEFGH")
            .qrcode(265, 30, TSCConst.EC_LEVEL_H, 4, TSCConst.QRCODE_MODE_MANUAL, TSCConst.ROTATION_0, "test qrcode")
            .text(200, 144, TSCConst.FNT_16_24, TSCConst.ROTATION_0, 1, 1, "Test EN")
            .text(38, 165, TSCConst.FNT_16_24, TSCConst.ROTATION_0, 1, 2, "HELLO")
            .bar(200, 183, 166, 30)
            .bar(334, 145, 30, 30)
            .print(1)
    }

    private fun printText() {
        printer.sizeMm(60.0, 30.0)
            .density(10)
            .reference(0, 0)
            .direction(TSCConst.DIRECTION_FORWARD)
            .cls()
            .text(10, 10, TSCConst.FNT_8_12, 2, 2, "123456")
            .print()
    }

    private fun printBarcode() {
        printer.sizeMm(60.0, 30.0)
            .gapMm(0.0, 0.0)
            .cls()
            .barcode(60, 50, TSCConst.CODE_TYPE_128, 108, "abcdef12345")
            .print()
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == 0 && resultCode == RESULT_OK) {
            try {
                val imagepath = data!!.data
                val resolver = contentResolver
                val b = MediaStore.Images.Media.getBitmap(resolver, imagepath)
                printPicCode(b)
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
    }

    private fun printPicCode(b: Bitmap) {
        printer.sizeMm(60.0, 40.0)
            .gapMm(2.0, 0.0)
            .cls()
            .bitmap(0, 0, TSCConst.BMP_MODE_OVERWRITE, 400, b)
            .print(1)
    }

}