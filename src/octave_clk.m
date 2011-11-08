fclk = 8000000
pre = [1 8 32 64 128 256 1024]
ftim = 40000
OCR = fclk./(2.*pre*ftim) - 1
OCR_entero = round(OCR)

err = ((OCR-OCR_entero)./OCR_entero) .*100

