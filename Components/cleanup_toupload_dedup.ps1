$base = 'd:\Dev\Flowcode V11\Components\'
$target = Join-Path $base 'ToUploadToWiki'

if (-not (Test-Path $target)) {
    Write-Output "Target folder not found: $target"
    exit 1
}

$timestamp = Get-Date -Format "yyyyMMdd_HHmmss"
$backup = Join-Path $target ("duplicates_removed_$timestamp")
New-Item -ItemType Directory -Path $backup | Out-Null

Write-Output "Scanning: $target"

$files = Get-ChildItem -Path $target -Recurse -File -Include '*.fcfx','*.fcsx','*.fcweb'

$groups = $files | Group-Object -Property {
    $ext = $_.Extension.ToLower()
    $name = [IO.Path]::GetFileNameWithoutExtension($_.Name)
    if ($name -match '^(.*)_(\d+)$') { $baseName = $matches[1] } else { $baseName = $name }
    return ($baseName.ToLower() + $ext)
}

foreach ($g in $groups) {
    $items = $g.Group | Sort-Object LastWriteTime -Descending
    $keep = $items[0]
    $keepNameNoExt = [IO.Path]::GetFileNameWithoutExtension($keep.Name)
    if ($keepNameNoExt -match '^(.*)_(\d+)$') { $canonicalBase = $matches[1] } else { $canonicalBase = $keepNameNoExt }
    $canonicalName = $canonicalBase + $keep.Extension
    $dest = Join-Path $target $canonicalName

    if ($keep.FullName -ieq $dest) {
        Write-Output "Keeping: $($keep.FullName)"
    } else {
        # Move the selected keep to the canonical root name
        Move-Item -Path $keep.FullName -Destination $dest -Force
        Write-Output "Moved keep: $($keep.FullName) -> $dest"
    }

    $others = $items | Select-Object -Skip 1
    foreach ($o in $others) {
        $safeName = ($o.FullName.Substring($target.Length)).TrimStart('\','/') -replace '[\\\/:]','_'
        $bkDest = Join-Path $backup $safeName
        $bkParent = Split-Path $bkDest -Parent
        if (-not (Test-Path $bkParent)) { New-Item -ItemType Directory -Path $bkParent | Out-Null }
        Move-Item -Path $o.FullName -Destination $bkDest -Force
        Write-Output "Moved duplicate: $($o.FullName) -> $bkDest"
    }
}

# Remove empty directories (except the backup folder)
Get-ChildItem -Path $target -Directory -Recurse | Where-Object { $_.FullName -ne $backup } | Sort-Object FullName -Descending | ForEach-Object {
    if (-not (Get-ChildItem -Path $_.FullName -Force -ErrorAction SilentlyContinue)) {
        Remove-Item $_.FullName -Force -Recurse -ErrorAction SilentlyContinue
        Write-Output "Removed empty dir: $($_.FullName)"
    }
}

Write-Output "Done. Duplicates moved to: $backup"
