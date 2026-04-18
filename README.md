# Procesare de text - frecventa cuvintelor

Proiect APD in C++ pentru calcularea frecventei cuvintelor dintr-un fisier text mare. Versiunea din acest repository este varianta secventiala, folosita ca baza pentru compararea cu variantele paralele OpenMP si `std::thread`.

## Structura

- `apd/apd.cpp` - implementarea secventiala.
- `data/input_sample.txt` - fisier de test inclus in repository.
- `data/input_large.txt` - set de date mai mare, generat determinist pentru experimente.
- `tools/generate_dataset.ps1` - script pentru regenerarea setului de date mare.
- `docs/gdoc_documentatie.md` - documentatia ceruta pentru Google Docs.
- `apd.sln` si `apd/apd.vcxproj` - proiect Visual Studio 2022.

## Rulare

Build Release x64 din Visual Studio sau cu MSBuild:

```powershell
& "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" .\apd.sln /p:Configuration=Release /p:Platform=x64
```

Rulare:

```powershell
.\x64\Release\apd.exe .\data\input_sample.txt .\results\frecvente_sample.csv
```

Programul afiseaza timpul de executie pentru varianta secventiala si salveaza frecventele sortate descrescator in CSV.

Regenerare dataset mare:

```powershell
powershell -ExecutionPolicy Bypass -File .\tools\generate_dataset.ps1 -OutputPath .\data\input_large.txt -Lines 100000
```
