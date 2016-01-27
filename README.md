# 4d-plugin-qrencode
4D plugin to generate QR code.

##Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|10.6|10.8|⭕️|⭕️|

Commands
---

```
QRCODE
```

Example
---
```
C_TEXT($data)
C_PICTURE($picture)

$version:=1
$size:=9
$margin:=1
$dpi:=96

$picture:=QRCODE ("www.wakanda.org";QR Format PNG;QR Mode Unicode;QR Correction Level L;$version;$size;$margin;$dpi;$data)
WRITE PICTURE FILE(System folder(Desktop)+"qr-test.png";$picture)
  //data is base64 encoded png

$picture:=QRCODE ("www.wakanda.org";QR Format SVG;QR Mode Unicode;QR Correction Level L;$version;$size;$margin;$dpi;$data)
WRITE PICTURE FILE(System folder(Desktop)+"qr-test.svg";$picture)
  //data is the svg source

SET PICTURE TO PASTEBOARD($picture)
```
Pass a combination of flags to ```QR Mode Unicode```, ```QR Mode Kanji```, and ```QR Mode Micro``` to ```mode```.
