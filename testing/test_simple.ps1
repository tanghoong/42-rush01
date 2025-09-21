# PowerShell test script for 42-rush01 skyscraper puzzle
# This script mimics the logic of test.c

Write-Host "Starting Rush-01 Skyscraper Puzzle Test" -ForegroundColor Green

# Test case parameters
$testCase = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"

Write-Host "Test Case: $testCase" -ForegroundColor Cyan

# Change to the gpt directory where the C files are located
$originalLocation = Get-Location
Set-Location "gpt"

# Check if executable exists, if not compile it
if (-not (Test-Path "rush-01.exe")) {
    Write-Host "Compiling the program..." -ForegroundColor Yellow
    
    if (Test-Path "Makefile") {
        & make
    } else {
        & gcc -Wall -Wextra -Werror -o rush-01.exe main.c parser.c solver.c check.c output.c utils.c vis.c
    }
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Compilation failed!" -ForegroundColor Red
        Set-Location $originalLocation
        exit 1
    }
    
    Write-Host "Compilation successful!" -ForegroundColor Green
}

# Run the program with the test case
Write-Host "Running test case..." -ForegroundColor Yellow

if (Test-Path "rush-01.exe") {
    $testArgs = $testCase.Split(' ')
    $result = & .\rush-01.exe @testArgs
    $exitCode = $LASTEXITCODE
    
    Write-Host "Program output:" -ForegroundColor Cyan
    Write-Host $result
    
    # Analyze the result
    if ($exitCode -eq 0) {
        Write-Host "✓ Test PASSED: Program executed successfully" -ForegroundColor Green
    } else {
        Write-Host "✗ Test FAILED: Program returned exit code $exitCode" -ForegroundColor Red
    }
} else {
    Write-Host "✗ Error: Executable not found" -ForegroundColor Red
    Set-Location $originalLocation
    exit 1
}

# Return to original location
Set-Location $originalLocation

Write-Host "`nTest completed." -ForegroundColor Green