# PowerShell test script for 42-rush01 skyscraper puzzle
# This script mimics the logic of test.c

Write-Host "Starting Rush-01 Skyscraper Puzzle Test" -ForegroundColor Green

# Test case parameters
$testCase = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
$expectedResult = $true  # We expect this test case to be solvable

Write-Host "Test Case: $testCase" -ForegroundColor Cyan

# Change to the gpt directory where the C files are located
$originalLocation = Get-Location
Set-Location "gpt"

try {
    # Check if executable exists, if not compile it
    if (-not (Test-Path "rush-01.exe")) {
        Write-Host "Compiling the program..." -ForegroundColor Yellow
        
        # Use make to compile
        if (Test-Path "Makefile") {
            & make
        } else {
            # Fallback compilation
            & gcc -Wall -Wextra -Werror -o rush-01.exe main.c parser.c solver.c check.c output.c utils.c vis.c
        }
        
        if ($LASTEXITCODE -ne 0) {
            Write-Host "Compilation failed!" -ForegroundColor Red
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
            
            # Check if output contains a valid solution (4x4 grid)
            $lines = $result -split "`n" | Where-Object { $_.Trim() -ne "" }
            $gridLines = $lines | Where-Object { $_ -match '^\s*[1-4]\s+[1-4]\s+[1-4]\s+[1-4]\s*$' }
            
            if ($gridLines.Count -eq 4) {
                Write-Host "✓ Valid 4x4 solution grid detected" -ForegroundColor Green
                
                # Display the solution nicely
                Write-Host "`nSolution Grid:" -ForegroundColor Magenta
                Write-Host "┌─────────┐"
                foreach ($line in $gridLines) {
                    $formattedLine = $line.Trim() -replace '\s+', ' '
                    Write-Host "│ $formattedLine │"
                }
                Write-Host "└─────────┘"
            } else {
                Write-Host "⚠ Warning: Expected 4x4 grid not found in output" -ForegroundColor Orange
            }
            
        } else {
            Write-Host "✗ Test FAILED: Program returned exit code $exitCode" -ForegroundColor Red
        }
        
    } else {
        Write-Host "✗ Error: Executable not found" -ForegroundColor Red
        exit 1
    }
    
} catch {
    Write-Host "✗ Error occurred: $($_.Exception.Message)" -ForegroundColor Red
    exit 1
} finally {
    # Return to original location
    Set-Location $originalLocation
}

Write-Host "`nTest completed." -ForegroundColor Green

# Additional test cases (optional)
Write-Host "`nRunning additional test cases..." -ForegroundColor Cyan

$additionalTests = @(
    "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1",
    "2 1 3 2 3 2 1 4 2 4 1 3 4 1 2 3"
)

Set-Location "gpt"

for ($i = 0; $i -lt $additionalTests.Count; $i++) {
    $test = $additionalTests[$i]
    Write-Host "`nAdditional Test $($i + 1): $test" -ForegroundColor Yellow
    
    try {
        $testArgs = $test.Split(' ')
        $result = & .\rush-01.exe @testArgs
        $exitCode = $LASTEXITCODE
        
        if ($exitCode -eq 0) {
            Write-Host "✓ Additional test $($i + 1) PASSED" -ForegroundColor Green
        } else {
            Write-Host "✗ Additional test $($i + 1) FAILED (exit code: $exitCode)" -ForegroundColor Red
        }
    } catch {
        Write-Host "✗ Additional test $($i + 1) ERROR: $($_.Exception.Message)" -ForegroundColor Red
    }
}

Set-Location $originalLocation
Write-Host "`nAll tests completed!" -ForegroundColor Green