# 4d-plugin-qrencode
Generate QR code using [libqrencode 4.0.0](https://fukuchi.org/works/qrencode/)

### Platform

| carbon | cocoa | win32 | win64 |
|:------:|:-----:|:---------:|:---------:|
|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|<img src="https://cloud.githubusercontent.com/assets/1725068/22371562/1b091f0a-e4db-11e6-8458-8653954a7cce.png" width="24" height="24" />|

### Version

<img src="https://cloud.githubusercontent.com/assets/1725068/18940649/21945000-8645-11e6-86ed-4a0f800e5a73.png" width="32" height="32" /> <img src="https://cloud.githubusercontent.com/assets/1725068/18940648/2192ddba-8645-11e6-864d-6d5692d55717.png" width="32" height="32" />

### Releases

[2.0](https://github.com/miyako/4d-plugin-qrencode/releases/tag/2.0) new ``mode`` constant: ``QR Mode Latin``, added Swiss QR example

[1.0](https://github.com/miyako/4d-plugin-qrencode/releases/tag/1.0)

---

## Syntax

```
barcode:=QRCODE (inData;inOutputFormat;inMode;inErrorCorrectionLevel;inVersion;inSize;inMargin;inDPI;outData)
```

Parameter|Type|Description
------------|------------|----
inData|TEXT|
inOutputFormat|LONGINT|
inMode|LONGINT|
inErrorCorrectionLevel|LONGINT|
inVersion|LONGINT|
inSize|LONGINT|
inMargin|LONGINT|
inDPI|LONGINT|
outData|TEXT|

```
QRCODE ARRAY (inData;inOutputFormat;inMode;inErrorCorrectionLevel;inVersion;inSize;inMargin;inDPI;outData)
```

Parameter|Type|Description
------------|------------|----
inData|TEXT|
inOutputFormat|LONGINT|
inMode|LONGINT|
inErrorCorrectionLevel|LONGINT|
inVersion|LONGINT|
inSize|LONGINT|
inMargin|LONGINT|
inDPI|LONGINT|
outData|ARRAY PICTURE|

## Examples

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
