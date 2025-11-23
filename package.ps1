# Build the project in Release mode
Write-Host "Building project in Release mode..."
cmake --build build --config Release

# Create a distribution directory
$distDir = "dist"
if (Test-Path $distDir) {
    Remove-Item -Recurse -Force $distDir
}
New-Item -ItemType Directory -Path $distDir | Out-Null

# Copy the executable
# Note: The executable path might vary depending on the generator, but for MSVC it's usually build/Release/
$exePath = "build/Release/MyRaylibProject.exe"
if (Test-Path $exePath) {
    Copy-Item $exePath -Destination $distDir
    Write-Host "Copied executable."
} else {
    Write-Error "Executable not found at $exePath. Make sure the build succeeded."
    exit 1
}

# Copy the textures folder
if (Test-Path "textures") {
    Copy-Item -Recurse "textures" -Destination $distDir
    Write-Host "Copied textures."
} else {
    Write-Warning "Textures folder not found."
}

# Zip the distribution folder
$zipFile = "MyRaylibProject.zip"
if (Test-Path $zipFile) {
    Remove-Item $zipFile
}
Compress-Archive -Path "$distDir/*" -DestinationPath $zipFile

Write-Host "Build and packaging complete! Zip file created: $zipFile"
