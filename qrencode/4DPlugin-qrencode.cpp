/* --------------------------------------------------------------------------------
 #
 #  4DPlugin-qrencode.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : qrencode
 #	author : miyako
 #	2019/10/10
 #  
 # --------------------------------------------------------------------------------*/

#include "4DPlugin-qrencode.h"

#pragma mark -

void PluginMain(PA_long32 selector, PA_PluginParameters params) {
    
	try
	{
        switch(selector)
        {
			// --- qrencode
            
			case 1 :
				QRCODE(params);
				break;
			case 2 :
				QRCODE_ARRAY(params);
				break;

        }

	}
	catch(...)
	{

	}
}

#pragma mark -

void QRCODE(PA_PluginParameters params) {
    
    sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
    PackagePtr pParams = (PackagePtr)params->fParameters;

    C_TEXT _data;
    C_LONGINT _format;
    C_LONGINT _mode;
    C_LONGINT _level;
    C_LONGINT _version;
    C_LONGINT _size;
    C_LONGINT _margin;
    C_LONGINT _dpi;
    C_TEXT _dump;
    //    C_PICTURE returnValue;
    
    _data.fromParamAtIndex(pParams, 1);
    _format.fromParamAtIndex(pParams, 2);
    _mode.fromParamAtIndex(pParams, 3);
    _level.fromParamAtIndex(pParams, 4);
    _version.fromParamAtIndex(pParams, 5);
    _size.fromParamAtIndex(pParams, 6);
    _margin.fromParamAtIndex(pParams, 7);
    _dpi.fromParamAtIndex(pParams, 8);
    
    int micro = (_mode.getIntValue() & QR_Mode_Micro);
    int swiss = (_mode.getIntValue() & QR_Mode_Swiss);
    int version = _version.getIntValue(); version = version > 0 ? version : 1;
    int dpi = _dpi.getIntValue(); dpi = dpi > 0 ? dpi : 72;
    int size = _size.getIntValue(); size = size > 0 ? size : 3;
    int margin = _margin.getIntValue(); margin = margin < 0 ? 0 : margin;
    output_type_t type = _format.getIntValue() == QR_OUTPUT_SVG ? QR_OUTPUT_SVG : QR_OUTPUT_PNG;
    QRencodeMode mode = (_mode.getIntValue() & QR_Mode_Kanji) ? QR_MODE_KANJI : QR_MODE_8;
    QRecLevel level = (QRecLevel)_level.getIntValue(); level = level ? level : QR_ECLEVEL_L;
    
    unsigned int len = 0;
    
    uint32_t dataSize = (_data.getUTF16Length() * sizeof(PA_Unichar) * 2)+ sizeof(uint8_t);
    std::vector<char> buf(dataSize);
    
    PA_4DCharSet encoding;
    
    switch (mode)
    {
        case QR_MODE_KANJI:
        encoding = eVTC_SHIFT_JIS;
        break;
        default:
        encoding = eVTC_UTF_8;
        break;
    }
    
    if (swiss)
    {
        encoding = eVTC_ISO_8859_1;
        mode = QR_MODE_AN;
    }
    
    len = PA_ConvertCharsetToCharset((char *)_data.getUTF16StringPtr(),
                                     _data.getUTF16Length() * sizeof(PA_Unichar),
                                     eVTC_UTF_16,
                                     (char *)&buf[0],
                                     dataSize,
                                     encoding);
    
    QRcode *qr = NULL;
    
    if(micro){
        
        if(mode == QR_MODE_KANJI){
            
            qr = QRcode_encodeStringMQR((const char *)&buf[0],
                                        version,
                                        level,
                                        mode,
                                        1);
            
        }else{
            
            qr = QRcode_encodeDataMQR((int)len,
                                      (const unsigned char *)&buf[0],
                                      version,
                                      level);
        }
        
    }else{
        
        if(mode == QR_MODE_KANJI){
            
            qr = QRcode_encodeString((const char *)&buf[0],
                                     version,
                                     level,
                                     mode,
                                     1);
            
        }else{
            
            qr = QRcode_encodeData((int)len,
                                   (const unsigned char *)&buf[0],
                                   version,
                                   level);
            
        }
        
    }
    
    if(qr){
        
        switch(type){
            case QR_OUTPUT_PNG:
            toPNG(qr, margin, size, dpi, _dump, pResult);
            break;
            
            case QR_OUTPUT_SVG:
            toSVG(qr, margin, size, dpi, _dump, pResult);
            break;
        }
        
        QRcode_free(qr);
        
    }
    
    _dump.toParamAtIndex(pParams, 9);
    
}

void QRCODE_ARRAY(PA_PluginParameters params) {
    
//    sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
    PackagePtr pParams = (PackagePtr)params->fParameters;

    C_TEXT _data;
    C_LONGINT _format;
    C_LONGINT _mode;
    C_LONGINT _level;
    C_LONGINT _version;
    C_LONGINT _size;
    C_LONGINT _margin;
    C_LONGINT _dpi;
    
    _data.fromParamAtIndex(pParams, 1);
    _format.fromParamAtIndex(pParams, 2);
    _mode.fromParamAtIndex(pParams, 3);
    _level.fromParamAtIndex(pParams, 4);
    _version.fromParamAtIndex(pParams, 5);
    _size.fromParamAtIndex(pParams, 6);
    _margin.fromParamAtIndex(pParams, 7);
    _dpi.fromParamAtIndex(pParams, 8);
    
    int version = _version.getIntValue(); version = version > 0 ? version : 1;
    int dpi = _dpi.getIntValue(); dpi = dpi > 0 ? dpi : 72;
    int size = _size.getIntValue(); size = size > 0 ? size : 3;
    int margin = _margin.getIntValue(); margin = margin < 0 ? 0 : margin;
    output_type_t type = _format.getIntValue() == QR_OUTPUT_SVG ? QR_OUTPUT_SVG : QR_OUTPUT_PNG;
    QRencodeMode mode = (_mode.getIntValue() & QR_Mode_Kanji) ? QR_MODE_KANJI : QR_MODE_8;
    QRecLevel level = (QRecLevel)_level.getIntValue(); level = level ? level : QR_ECLEVEL_L;
    
    //picture array
    PA_Variable Param9 = *((PA_Variable*) pParams[8]);
    switch (Param9.fType)
    {
        case eVK_ArrayPicture:
        break;
        case eVK_Undefined:
        PA_ClearVariable(&Param9);
        Param9 = PA_CreateVariable(eVK_ArrayPicture);
        break;
        default:
        break;
    }
    
    if (Param9.fType == eVK_ArrayPicture)
    {
        PA_ResizeArray(&Param9, 0);
        
        unsigned int len = 0;
        
        uint32_t dataSize = (_data.getUTF16Length() * sizeof(PA_Unichar) * 2)+ sizeof(uint8_t);
        std::vector<char> buf(dataSize);
        
        PA_4DCharSet encoding;
        
        switch (mode)
        {
            case QR_MODE_KANJI:
            encoding = eVTC_SHIFT_JIS;
            break;
            default:
            encoding = eVTC_UTF_8;
            break;
        }
        
        len = PA_ConvertCharsetToCharset((char *)_data.getUTF16StringPtr(),
                                         _data.getUTF16Length() * sizeof(PA_Unichar),
                                         eVTC_UTF_16,
                                         (char *)&buf[0],
                                         dataSize,
                                         encoding);
        
        QRcode_List *qrl = NULL;
        
        if (mode == QR_MODE_KANJI)
        {
            qrl = QRcode_encodeStringStructured((const char *)&buf[0],
                                                version,
                                                level,
                                                mode,
                                                1);
        }else
        {
            qrl = QRcode_encodeDataStructured((int)len,
                                              (const unsigned char *)&buf[0],
                                              version,
                                              level);
        }
        
        if (qrl)
        {
            int count = QRcode_List_size(qrl);
            QRcode *qr;
            for (unsigned int i = 0; i < count; ++i)
            {
                if(qrl)
                {
                    qr = qrl->code;
                    
                    switch (type)
                    {
                        case QR_OUTPUT_PNG:
                        toPNGs(qr, margin, size, dpi, i + 1, &Param9);
                        break;
                        
                        case QR_OUTPUT_SVG:
                        toSVGs(qr, margin, size, dpi, i + 1, &Param9);
                        break;
                    }
                    
                    qrl = qrl->next;
                }
                else
                {
                    break;
                }
            }
            QRcode_List_free(qrl);
        }
        
        PA_Variable *param9 = ((PA_Variable *)pParams[8]);
        
        param9->fType = Param9.fType;
        param9->fFiller = Param9.fFiller;
        param9->uValue.fArray.fCurrent = Param9.uValue.fArray.fCurrent;
        param9->uValue.fArray.fNbElements = Param9.uValue.fArray.fNbElements;
        param9->uValue.fArray.fData = Param9.uValue.fArray.fData;
        
    }
}

void toSVGs(QRcode *qr, int margin, int size, int dpi, int pos, PA_Variable *param)
{
    margin = margin * size;
    
    char _size[33];
    sprintf(_size, "%d", size);
    
    char _width[33];
    sprintf(_width, "%d", margin + (qr->width * size) + margin);
    
    char _dpi[33];
    sprintf(_dpi, "%d", dpi);
    
    char _margin[33];
    sprintf(_margin, "%d", margin);
    
    char _x[33];
    char _y[33];
    
    std::string svg;
    
    svg += "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
    svg += "<svg width=\"100%\" height=\"100%\" viewBox=\"0 0 ";
    svg += _width;
    svg += " ";
    svg += _width;
    svg += "\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:ns4d=\"http://www.4d.com\" ns4d:DPI=\"";
    svg += _dpi;
    svg += "\">\n";
    svg += "<g shape-rendering=\"crispEdges\" stroke-width=\"0\" stroke=\"none\" transform=\"translate(";
    svg += _margin;
    svg += ",";
    svg += _margin;
    svg += ")\">\n";
    
    unsigned char *p;
    int x, y = 0, i, j;
    
    p = qr->data;
    
    for(i = 0; i < qr->width; ++i)
    {
        //        PA_YieldAbsolute();
        x = 0;
        sprintf(_y, "%d", y);
        
        for(j = 0; j < qr->width; ++j)
        {
            sprintf(_x, "%d", x);
            
            if(*p&1)
            {
                svg += "<rect fill=\"black\" stroke=\"black\" height=\"";
                svg += _size;
                svg += "\" width=\"";
                svg += _size;
                svg += "\" ";
            }else{
                svg += "<rect fill=\"white\" stroke=\"white\" height=\"";
                svg += _size;
                svg += "\" width=\"";
                svg += _size;
                svg += "\" ";
            }
            
            svg += "x=\"";
            svg += _x;
            svg += "\" ";
            svg += "y=\"";
            svg += _y;
            svg += "\" />\n";
            
            p++;
            x = x + size;
            
        }
        y = y + size;
    }
    
    svg += "</g>\n";
    svg += "</svg>\n";
    
    PA_Picture picture = PA_CreatePicture((void *)svg.c_str(), svg.size());
    PA_ResizeArray(param, pos);
    PA_SetPictureInArray(*param, pos, picture);
}

void toPNGs(QRcode *qr, int margin, int size, int dpi, int pos, PA_Variable *param)
{
    unsigned int fg_color[4] = {0, 0, 0, 255};
    unsigned int bg_color[4] = {255, 255, 255, 255};
    
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;
    png_byte alpha_values[2];
    unsigned char *row, *p, *q;
    int x, y, xx, yy, bit;
    int realwidth;
    
    realwidth = (qr->width + margin * 2) * size;
    row = (unsigned char *)malloc((realwidth + 7) / 8);
    if(row != NULL) {
        
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if(png_ptr != NULL) {
            
            info_ptr = png_create_info_struct(png_ptr);
            if(info_ptr != NULL) {
                
                if(setjmp(png_jmpbuf(png_ptr))) {
                    png_destroy_write_struct(&png_ptr, &info_ptr);
                }else{
                    
                    palette = (png_colorp) malloc(sizeof(png_color) * 2);
                    if(palette != NULL) {
                        
                        palette[0].red   = fg_color[0];
                        palette[0].green = fg_color[1];
                        palette[0].blue  = fg_color[2];
                        palette[1].red   = bg_color[0];
                        palette[1].green = bg_color[1];
                        palette[1].blue  = bg_color[2];
                        alpha_values[0] = fg_color[3];
                        alpha_values[1] = bg_color[3];
                        png_set_PLTE(png_ptr, info_ptr, palette, 2);
                        png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);
                        
                        C_BLOB png;
                        
                        png_set_write_fn(png_ptr, (png_voidp)&png, write_data_fn, output_flush_fn);
                        
                        png_set_IHDR(png_ptr, info_ptr,
                                     realwidth, realwidth,
                                     1,
                                     PNG_COLOR_TYPE_PALETTE,
                                     PNG_INTERLACE_NONE,
                                     PNG_COMPRESSION_TYPE_DEFAULT,
                                     PNG_FILTER_TYPE_DEFAULT);
                        png_set_pHYs(png_ptr, info_ptr,
                                     dpi * INCHES_PER_METER,
                                     dpi * INCHES_PER_METER,
                                     PNG_RESOLUTION_METER);
                        
                        png_write_info(png_ptr, info_ptr);
                        
                        /* top margin */
                        memset(row, 0xff, (realwidth + 7) / 8);
                        for(y=0; y<margin * size; y++) {
                            png_write_row(png_ptr, row);
                        }
                        
                        /* data */
                        p = qr->data;
                        for(y=0; y<qr->width; y++) {
                            //                            PA_YieldAbsolute();
                            bit = 7;
                            memset(row, 0xff, (realwidth + 7) / 8);
                            q = row;
                            q += margin * size / 8;
                            bit = 7 - (margin * size % 8);
                            for(x=0; x<qr->width; x++) {
                                for(xx=0; xx<size; xx++) {
                                    *q ^= (*p & 1) << bit;
                                    bit--;
                                    if(bit < 0) {
                                        q++;
                                        bit = 7;
                                    }
                                }
                                p++;
                            }
                            for(yy=0; yy<size; yy++) {
                                png_write_row(png_ptr, row);
                            }
                        }
                        
                        /* bottom margin */
                        memset(row, 0xff, (realwidth + 7) / 8);
                        for(y=0; y<margin * size; y++) {
                            png_write_row(png_ptr, row);
                        }
                        
                        png_write_end(png_ptr, info_ptr);
                        png_destroy_write_struct(&png_ptr, &info_ptr);
                        
                        free(row);
                        free(palette);
                        
                        PA_Picture picture = PA_CreatePicture((void *)png.getBytesPtr(), png.getBytesLength());
                        PA_ResizeArray(param, pos);
                        PA_SetPictureInArray(*param, pos, picture);
                        
                    }
                }
            }
        }
    }
}


void write_data_fn(png_structp png_ptr, png_bytep buf, png_size_t size){
    C_BLOB *blob = (C_BLOB *)png_get_io_ptr(png_ptr);
    blob->addBytes((const uint8_t *)buf, (uint32_t)size);
}

void output_flush_fn(png_structp png_ptr)
{
    
}

void toSVG(QRcode *qr, int margin, int size, int dpi, C_TEXT &_dump, sLONG_PTR *pResult)
{
    margin = margin * size;
    
    char _size[33];
    sprintf(_size, "%d", size);
    
    char _width[33];
    sprintf(_width, "%d", margin + (qr->width * size) + margin);
    
    char _dpi[33];
    sprintf(_dpi, "%d", dpi);
    
    char _margin[33];
    sprintf(_margin, "%d", margin);
    
    char _x[33];
    char _y[33];
    
    std::string svg;
    
    svg += "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n";
    svg += "<svg width=\"100%\" height=\"100%\" viewBox=\"0 0 ";
    svg += _width;
    svg += " ";
    svg += _width;
    svg += "\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:ns4d=\"http://www.4d.com\" ns4d:DPI=\"";
    svg += _dpi;
    svg += "\">\n";
    svg += "<g shape-rendering=\"crispEdges\" stroke-width=\"0\" stroke=\"none\" transform=\"translate(";
    svg += _margin;
    svg += ",";
    svg += _margin;
    svg += ")\">\n";
    
    unsigned char *p;
    int x, y = 0, i, j;
    
    p = qr->data;
    
    for(i = 0; i < qr->width; ++i)
    {
        //        PA_YieldAbsolute();
        x = 0;
        sprintf(_y, "%d", y);
        
        for(j = 0; j < qr->width; ++j)
        {
            sprintf(_x, "%d", x);
            
            if(*p&1)
            {
                svg += "<rect fill=\"black\" stroke=\"black\" height=\"";
                svg += _size;
                svg += "\" width=\"";
                svg += _size;
                svg += "\" ";
            }else{
                svg += "<rect fill=\"white\" stroke=\"white\" height=\"";
                svg += _size;
                svg += "\" width=\"";
                svg += _size;
                svg += "\" ";
            }
            
            svg += "x=\"";
            svg += _x;
            svg += "\" ";
            svg += "y=\"";
            svg += _y;
            svg += "\" />\n";
            
            p++;
            x = x + size;
            
        }
        y = y + size;
    }
    
    svg += "</g>\n";
    svg += "</svg>\n";
    
    CUTF8String _svg((const uint8_t *)svg.c_str());
    
    _dump.setUTF8String(&_svg);
    
    PA_Picture picture = PA_CreatePicture((void *)svg.c_str(), svg.size());
    *(PA_Picture*) pResult = picture;
}

void toPNG(QRcode *qr, int margin, int size, int dpi, C_TEXT &_dump, sLONG_PTR *pResult)
{
    unsigned int fg_color[4] = {0, 0, 0, 255};
    unsigned int bg_color[4] = {255, 255, 255, 255};
    
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;
    png_byte alpha_values[2];
    unsigned char *row, *p, *q;
    int x, y, xx, yy, bit;
    int realwidth;
    
    realwidth = (qr->width + margin * 2) * size;
    row = (unsigned char *)malloc((realwidth + 7) / 8);
    if(row != NULL) {
        
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if(png_ptr != NULL) {
            
            info_ptr = png_create_info_struct(png_ptr);
            if(info_ptr != NULL) {
                
                if(setjmp(png_jmpbuf(png_ptr))) {
                    png_destroy_write_struct(&png_ptr, &info_ptr);
                }else{
                    
                    palette = (png_colorp) malloc(sizeof(png_color) * 2);
                    if(palette != NULL) {
                        
                        palette[0].red   = fg_color[0];
                        palette[0].green = fg_color[1];
                        palette[0].blue  = fg_color[2];
                        palette[1].red   = bg_color[0];
                        palette[1].green = bg_color[1];
                        palette[1].blue  = bg_color[2];
                        alpha_values[0] = fg_color[3];
                        alpha_values[1] = bg_color[3];
                        png_set_PLTE(png_ptr, info_ptr, palette, 2);
                        png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);
                        
                        C_BLOB png;
                        
                        png_set_write_fn(png_ptr, (png_voidp)&png, write_data_fn, output_flush_fn);
                        
                        png_set_IHDR(png_ptr, info_ptr,
                                     realwidth, realwidth,
                                     1,
                                     PNG_COLOR_TYPE_PALETTE,
                                     PNG_INTERLACE_NONE,
                                     PNG_COMPRESSION_TYPE_DEFAULT,
                                     PNG_FILTER_TYPE_DEFAULT);
                        png_set_pHYs(png_ptr, info_ptr,
                                     dpi * INCHES_PER_METER,
                                     dpi * INCHES_PER_METER,
                                     PNG_RESOLUTION_METER);
                        
                        png_write_info(png_ptr, info_ptr);
                        
                        /* top margin */
                        memset(row, 0xff, (realwidth + 7) / 8);
                        for(y=0; y<margin * size; y++) {
                            png_write_row(png_ptr, row);
                        }
                        
                        /* data */
                        p = qr->data;
                        for(y=0; y<qr->width; y++) {
                            //                            PA_YieldAbsolute();
                            bit = 7;
                            memset(row, 0xff, (realwidth + 7) / 8);
                            q = row;
                            q += margin * size / 8;
                            bit = 7 - (margin * size % 8);
                            for(x=0; x<qr->width; x++) {
                                for(xx=0; xx<size; xx++) {
                                    *q ^= (*p & 1) << bit;
                                    bit--;
                                    if(bit < 0) {
                                        q++;
                                        bit = 7;
                                    }
                                }
                                p++;
                            }
                            for(yy=0; yy<size; yy++) {
                                png_write_row(png_ptr, row);
                            }
                        }
                        
                        /* bottom margin */
                        memset(row, 0xff, (realwidth + 7) / 8);
                        for(y=0; y<margin * size; y++) {
                            png_write_row(png_ptr, row);
                        }
                        
                        png_write_end(png_ptr, info_ptr);
                        png_destroy_write_struct(&png_ptr, &info_ptr);
                        
                        free(row);
                        free(palette);
                        
                        PA_Picture picture = PA_CreatePicture((void *)png.getBytesPtr(), png.getBytesLength());
                        *(PA_Picture*) pResult = picture;
                        
                        png.toB64Text(&_dump);
                        
                    }
                }
            }
        }
    }
}
