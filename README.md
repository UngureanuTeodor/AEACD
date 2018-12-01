# AEACD

> OCR prin votare și tool de corectare al textului rezultat  
  
### State-of-the-art  

**Tesseract**
- Tool pentru recunoașterea textului în imagini
- Open-source
- Suportă multe format-uri de imagini
- Output-ul este un fișier text  
  
### Pașii procesului  
  
**Preprocesare**  
- [x] Binarizare
	- [x] Otsu thresholding
	- [x] Adaptive thresholding
- [x] Skew & Noise removal
- [ ] Opțional: Border removal
- [ ] Analiză layout
	- [ ] Hough transformations - obținând coordonatele fiecărui element din imagine (masks)  
  
**Filtre individuale**  
Input: imaginea obținută după preprocesare  
- [ ] Aplicare de filtre individuale sau în combinație
	- [ ] Blur correction
	- [ ] Illumination correction
	- [ ] Edge enhancement
	- [ ] Operații morfologice de dilatare și eroziune  
  
**OCR Engines**  
Input: 
	1. Variațiile de imagini după filtrări
	2. Coordonatele obținute prin segmentare  
Scop: 
	- [ ] Transformarea imaginii în text
	- [ ] Returnarea acurateții  
OCR Engine-uri: Tesseract, ABBYY FineReader Engine, Asprise OCR  

**Acuratețe**  
- [ ] Sistem de votare - implementarea unui sistem pentru a alege cel mai bun text returnat de engine-ul OCR curent
- [ ] Compararea acurateții folosind cifrele întoarse odată cu textul din OCR engine  

**Reconstruire și Tool de corecție**  
- [ ] Reconstruire
	- [ ] Într-un fișier text cu delimitatori
	- [ ] Într-un fișier format .pdf
- [ ] Tool de corecție  

### Milestones  

**Milestone 1**  
- [x] Otsu thresholding
- [x] Adaptive thresholding
- [x] Skew detection and correction
- [x] Noise removal  

**Milestone 2**  
- [ ] Finalizare preprocesare
- [ ] Aplicare filtre
- [ ] Lucru cu OCR engines  

**Milestone 3**  
- [ ] Sistem de votare pentru acuratețe
- [ ] Reconstruire
- [ ] Tool de corecție
- [ ] Statistici