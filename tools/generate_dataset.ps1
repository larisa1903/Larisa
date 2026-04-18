param(
    [string]$OutputPath = "data/input_large.txt",
    [int]$Lines = 100000
)

$sentences = @(
    "Parallel text processing counts words in large files and compares performance.",
    "The sequential baseline reads tokens normalizes punctuation and updates frequencies.",
    "OpenMP and std thread implementations can split work across multiple cores.",
    "Reliable experiments use the same input data and the same release build.",
    "Word frequency analysis is a common text processing workload."
)

$directory = Split-Path -Parent $OutputPath
if ($directory) {
    New-Item -ItemType Directory -Force -Path $directory | Out-Null
}

$writer = [System.IO.StreamWriter]::new($OutputPath, $false, [System.Text.Encoding]::UTF8)
try {
    for ($i = 0; $i -lt $Lines; $i++) {
        $writer.WriteLine($sentences[$i % $sentences.Count])
    }
}
finally {
    $writer.Dispose()
}

Write-Host "Generated $Lines lines in $OutputPath"
