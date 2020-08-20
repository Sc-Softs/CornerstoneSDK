$config_type = $args[0]

$start_location = Resolve-Path .

$psscript = Split-Path -Leaf $MyInvocation.MyCommand.Definition

if ($null -eq $config_type) {
    Write-Warning "No configuration specified, using Debug as default, if you want release, use `"$psscript Release`" instead."
    $config_type = "Debug"
}
else{
    Write-Host "Building configuration $config_type"
}

If (-not (Test-Path ".\CMakeLists.txt")) {
    Write-Warning "CMakeList.txt not found."
    exit
}

try {
    $_v = (& cmake --version)
    Write-Host $_v[0]
}
catch {
    Write-Warning "CMake not found!"
    exit
}

if (-not (Test-Path -Path ".\build")) {
    New-Item -Path ".\build" -ItemType "directory" | Out-Null
    Write-Host "Create build folder."
}
$build_dir = Resolve-Path ".\build"

Set-Location $build_dir

Write-Host "Configuration begins." -ForegroundColor Green

Write-Host "Env:OS is $Env:OS"
try {
    $is_windows = ($Env:OS -match "Win")
}
catch {
    $is_windows = $false
}

if ($is_windows){
    Write-Host "Build for win32..."
    cmake -A "Win32"`
        -DCMAKE_CONFIGURATION_TYPES="$config_type" `
        ..
}else {
    Write-Host "Build for anything..."
    cmake `
        -DCMAKE_BUILD_TYPE="$config_type" `
        ..
}

Write-Host "Build begins." -ForegroundColor Green
cmake --build .  --config $config_type

Set-Location $start_location