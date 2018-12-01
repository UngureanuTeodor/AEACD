# AEACD

> OCR prin votare și tool de corectare al textului rezultat  

### State-of-the-art
<br />
**Tesseract**
- Tool pentru recunoașterea textului în imagini
- Open-source
- Suportă multe format-uri de imagini
- Output-ul este un fișier text
<br />
### Pașii procesului
**Preprocesare**
- [x] Binarizare
	- [x] Otsu thresholding
	- [x] Adaptive thresholding
- [x] Skew & Noise removal
- [ ] Opțional: Border removal
- [ ] Analiză layout
	- [ ] Hough transformations - obținând coordonatele fiecărui element din imagine (masks)
<br />
**Filtre individuale**
Input: imaginea obținută după preprocesare
Scop: 
	- [ ] Aplicare de filtre individuale sau în combinație:
		- [ ] Blur correction
		- [ ] Illumination correction
		- [ ] Edge enhancement
		- [ ] Operații morfologice de dilatare și eroziune
<br />
** OCR Engines**
Input: 
	1. Variațiile de imagini după filtrări
	2. Coordonatele obținute prin segmentare
Scop: 
	- [ ] Transformarea imaginii în text
	- [ ] Returnarea acurateții
OCR Engine-uri: Tesseract, ABBYY FineReader Engine, Asprise OCR
<br />
**Acuratețe**
- [ ] Sistem de votare - implementarea unui sistem pentru a alege cel mai bun text returnat de engine-ul OCR curent
- [ ] Compararea acurateții folosind cifrele întoarse odată cu textul din OCR engine
<br />
**Reconstruire și Tool de corecție**
- [ ] Reconstruire:
	- [ ] Într-un fișier text cu delimitatori
	- [ ] Într-un fișier format .pdf
- [ ] Tool de corecție
<br />
### Milestones
<br />
**Milestone 1**
- [x] Otsu thresholding
- [x] Adaptive thresholding
- [x] Skew detection and correction
- [x] Noise removal
<br />
**Milestone 2**
- [ ] Finalizare preprocesare
- [ ] Aplicare filtre
- [ ] Lucru cu OCR engines
<br />
**Milestone 3**
- [ ] Sistem de votare pentru acuratețe
- [ ] Reconstruire
- [ ] Tool de corecție
- [ ] Statistici