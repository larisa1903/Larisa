# Documentatie proiect APD - Procesare de text

## 1. Cerintele si tema proiectului

Topicul proiectului este procesarea de text. Programul calculeaza frecventa cuvintelor dintr-un fisier text mare, iar scopul proiectului este compararea unei variante secventiale cu variante paralele pentru imbunatatirea performantei.

Algoritm pentru varianta secventiala:

1. Se citeste fisierul de intrare token cu token.
2. Fiecare token este normalizat: literele sunt transformate in litere mici, iar semnele de punctuatie sunt eliminate.
3. Pentru fiecare cuvant valid se incrementeaza frecventa intr-un `std::unordered_map<std::string, std::size_t>`.
4. Rezultatele sunt copiate intr-un vector si sortate descrescator dupa frecventa, apoi alfabetic pentru frecvente egale.
5. Rezultatul este scris intr-un fisier CSV.

Limbaj de programare: C++.

Tehnologii planificate pentru versiunile paralele:

- OpenMP: paralelizare prin directive, impartind procesarea intre mai multe thread-uri.
- `std::thread`: paralelizare manuala folosind biblioteca standard C++.

Versiunea prezenta in repository este varianta secventiala de referinta.

## 2. Informatii despre masina de test

- Producator: HP
- Model: Victus by HP Gaming Laptop 15-fa0xxx
- Procesor: 12th Gen Intel(R) Core(TM) i5-12450H
- Numar nuclee fizice: 8
- Numar procesoare logice: 12
- Frecventa maxima raportata: 2000 MHz
- Memorie RAM: aproximativ 16 GB
- Sistem de operare: Windows
- Mediul de dezvoltare: Visual Studio 2022 Community, toolset MSVC v143

## 3. Rezultate experimentale

Masuratorile au fost efectuate pentru configuratia Release x64. Timpii reprezinta executia completa a variantei secventiale: citire fisier, normalizare, numarare, sortare si scriere CSV.

| Set de date | Dimensiune | Cuvinte distincte | Timp varianta secventiala |
| --- | ---: | ---: | ---: |
| `data/input_sample.txt` | 366 bytes | 45 | 1.338 ms |
| `data/input_large.txt` | 7,600,003 bytes | 45 | 189.796 ms |

Comanda folosita:

```powershell
.\x64\Release\apd.exe .\data\input_sample.txt .\results\frecvente_sample.csv
.\x64\Release\apd.exe .\data\input_large.txt .\results\frecvente_large.csv
```

Setul de date mare a fost generat determinist cu:

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\generate_dataset.ps1 -OutputPath .\data\input_large.txt -Lines 100000
```

Observatie: pentru raportul final, valorile pot fi extinse cu media mai multor rulari si cu rezultatele variantelor paralele OpenMP si `std::thread`.
