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

```
  //swiss qr iso-20022

C_OBJECT($Header)
OB SET($Header;\
"QRType";"SPC";\
"Version";"0100";\
"Coding";"1")

  //Konto
$IBAN:="CH4431999123000889012"

  //ZE
$Name:="Robert Schneider AG"
$StrtNm:="Rue du Lac"
$BldgNb:="1268"
$PstCd:="2501"
$TwnNm:="Biel"
$Ctry:="CH"

ASSERT(Match regex("[a-zA-Z]{2}[0-9]{2}[a-zA-Z0-9]{4}[0-9]{7}[a-zA-Z0-9]{0,16}";$IBAN))
ASSERT(Length($Name)<71)
ASSERT(Length($StrtNm)<71)
ASSERT(Length($BldgNb)<17)
ASSERT(Length($PstCd)<17)
ASSERT(Length($TwnNm)<36)
ASSERT(Match regex("[a-zA-Z]{2}";$Ctry))

C_OBJECT($Cdtr)
OB SET($Cdtr;\
"Name";$Name;\
"StrtNm";$StrtNm;\
"BldgNb";$BldgNb;\
"PstCd";$PstCd;\
"TwnNm";$TwnNm;\
"Ctry";Uppercase($Ctry))

C_OBJECT($CdtrInf)
OB SET($CdtrInf;\
"IBAN";Uppercase($IBAN);\
"Cdtr";$Cdtr)

$Name:="Robert Schneider Services Switzerland AG"

  //EZE
C_OBJECT($UltmtCdtr)
OB SET($UltmtCdtr;\
"Name";$Name;\
"StrtNm";$StrtNm;\
"BldgNb";$BldgNb;\
"PstCd";$PstCd;\
"TwnNm";$TwnNm;\
"Ctry";Uppercase($Ctry))

$Amt:="1949.75"
$Ccy:="CHF"
$ReqdExctnDt:="2019-10-31"

C_OBJECT($CcyAmtDate)
OB SET($CcyAmtDate;\
"Amt";$Amt;\
"Ccy";$Ccy;\
"ReqdExctnDt";$ReqdExctnDt)

  //EZP
$Name:="Pia-Maria Rutschmann-Schnyder"
$StrtNm:="Grosse Marktgasse"
$BldgNb:="28"
$PstCd:="9400"
$TwnNm:="Rorschach"
$Ctry:="CH"

C_OBJECT($UltmtDbtr)
OB SET($UltmtDbtr;\
"Name";$Name;\
"StrtNm";$StrtNm;\
"BldgNb";$BldgNb;\
"PstCd";$PstCd;\
"TwnNm";$TwnNm;\
"Ctry";$Ctry)

$Tp:="QRR"
$Ref:="210000000003139471430009017"
$Ustrd:="Auftrag vom 15.09.2019##S1/01/20170309/11/10201409/20/14000000/22/36958/30/CH106017086/40/1020/41/3010"

C_OBJECT($RmtInf)
OB SET($RmtInf;\
"Tp";$Tp;\
"Ref";$Ref;\
"Ustrd";$Ustrd)

ARRAY TEXT($AltPmt;2)
$AltPmt{1}:="UV1;1.1;1278564;1A-2F-43-AC-9B-33-21-B0-CC-D4-28-56;TCXVMKC22;2019-02-10T15:12:39; 2019-02-10T15:18:16"
$AltPmt{2}:="XY2;2a-2.2r;_R1-CH2_ConradCH-2074-1_3350_2019-03-13T10:23:47_16,99_0,00_0,00_0,00_0,00_+8FADt/DQ=_1=="

C_OBJECT($QRCH)
OB SET($QRCH;\
"Header";$Header;\
"CdtrInf";$CdtrInf;\
"UltmtCdtr";$UltmtCdtr;\
"CcyAmtDate";$CcyAmtDate;\
"UltmtDbtr";$UltmtDbtr;\
"RmtInf";$RmtInf)
OB SET ARRAY($QRCH;"AltPmtInf";$AltPmt)

$picture:=QRCH ($QRCH)

SET PICTURE TO PASTEBOARD($picture)
WRITE PICTURE FILE(System folder(Desktop)+"qr-test.png";$picture)
```

* QRCH

```
C_OBJECT($1;$QRCH)
C_PICTURE($0)

$QRCH:=$1

$code:=""
$code:=$code+OB Get(OB Get($QRCH;"Header");"QRType";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"Header");"Version";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"Header");"Coding";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"CdtrInf");"IBAN";Is text)+"\r\n"
$code:=$code+OB Get(OB Get(OB Get($QRCH;"CdtrInf");"Cdtr");"Name";Is text)+"\r\n"
$code:=$code+OB Get(OB Get(OB Get($QRCH;"CdtrInf");"Cdtr");"StrtNm";Is text)+"\r\n"
$code:=$code+OB Get(OB Get(OB Get($QRCH;"CdtrInf");"Cdtr");"BldgNb";Is text)+"\r\n"
$code:=$code+OB Get(OB Get(OB Get($QRCH;"CdtrInf");"Cdtr");"PstCd";Is text)+"\r\n"
$code:=$code+OB Get(OB Get(OB Get($QRCH;"CdtrInf");"Cdtr");"TwnNm";Is text)+"\r\n"
$code:=$code+OB Get(OB Get(OB Get($QRCH;"CdtrInf");"Cdtr");"Ctry";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtCdtr");"Name";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtCdtr");"StrtNm";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtCdtr");"BldgNb";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtCdtr");"PstCd";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtCdtr");"TwnNm";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtCdtr");"Ctry";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"CcyAmtDate");"Amt";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"CcyAmtDate");"Ccy";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"CcyAmtDate");"ReqdExctnDt";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtDbtr");"Name";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtDbtr");"StrtNm";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtDbtr");"BldgNb";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtDbtr");"PstCd";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtDbtr");"TwnNm";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"UltmtDbtr");"Ctry";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"RmtInf");"Tp";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"RmtInf");"Ref";Is text)+"\r\n"
$code:=$code+OB Get(OB Get($QRCH;"RmtInf");"Ustrd";Is text)

ARRAY TEXT($AltPmt;0)
OB GET ARRAY($QRCH;"AltPmtInf";$AltPmt)
If (Size of array($AltPmt)#0)
	$code:=$code+"\r\n"+$AltPmt{1}
End if 
If (Size of array($AltPmt)>1)
	$code:=$code+"\r\n"+$AltPmt{2}
End if 

$version:=1
$size:=3
$margin:=0
$dpi:=96

$picture:=QRCODE ($code;QR Format PNG;QR Mode Latin;QR Correction Level M;$version;$size;$margin;$dpi;$data)


READ PICTURE FILE(Get 4D folder(Current resources folder)+"CH-Kreuz_7mm.png";$cross)
PICTURE PROPERTIES($cross;$crossSize;$crossSize)  //166
$codeSize:=$crossSize/7*46  //Swiss QR code should be 46mm
PICTURE PROPERTIES($picture;$qrSize;$qrSize)
TRANSFORM PICTURE($picture;Scale;$codeSize/$qrSize;$codeSize/$qrSize)
PICTURE PROPERTIES($picture;$qrSize;$qrSize)
COMBINE PICTURES($picture;$picture;Superimposition;$cross;($qrSize/2)-($crossSize/2);($qrSize/2)-($crossSize/2))

$0:=$picture
```
