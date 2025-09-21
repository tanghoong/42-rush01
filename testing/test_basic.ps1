# PowerShell test script for 42-rush01 skyscraper puzzle
# This script mimics the logic of test.c

Write-Host "Starting Rush-01 Skyscraper Puzzle Test" -ForegroundColor Green

# Test case parameters (same as test.c)
$testCase = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"

Write-Host "Test Case: $testCase" -ForegroundColor Cyan

# Change to the gpt directory
$originalLocation = Get-Location
Set-Location "gpt"

# Check if executable exists
if (-not (Test-Path "rush-01")) {
    Write-Host "Compiling the program..." -ForegroundColor Yellow
    
    if (Test-Path "Makefile") {
        make
    } else {
        gcc -Wall -Wextra -Werror -o rush-01 main.c parser.c solver.c check.c output.c utils.c vis.c
    }
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "Compilation failed!" -ForegroundColor Red
        Set-Location $originalLocation
        exit 1
    }
    
    Write-Host "Compilation successful!" -ForegroundColor Green
}

# Run the test
Write-Host "Running test case..." -ForegroundColor Yellow

if (Test-Path "rush-01") {
    $testArgs = $testCase -split ' '
    $output = & .\rush-01 @testArgs
    
    Write-Host "Program output:" -ForegroundColor Cyan
    Write-Output $output
    
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Test PASSED!" -ForegroundColor Green
    } else {
        Write-Host "Test FAILED!" -ForegroundColor Red
    }
} else {
    Write-Host "Executable not found!" -ForegroundColor Red
}

# Return to original location
Set-Location $originalLocation
Write-Host "Test completed." -ForegroundColor Green