$sourceFile = "aaa.csv"  
$maxLines = 3000  
$currentFile = 1  
$currentLines = 0  
  
$outputFileBase = "output"  

  
$reader = New-Object System.IO.StreamReader($sourceFile)  
  
try {  
    while (!$reader.EndOfStream) {  
        $line = $reader.ReadLine()  
  
        # 如果需要，创建新文件  
        if ($currentLines -eq 0) {  
            $outputFile = [System.IO.Path]::Combine($outputDir, "$outputFileBase$currentFile.csv")  
            $writer = New-Object System.IO.StreamWriter($outputFile)  
        }  
  
        $writer.WriteLine($line)  
        $currentLines++  
  
        # 检查是否需要开始新文件  
        if ($currentLines -ge $maxLines) {  
            $writer.Close()  
            $writer.Dispose()  
            $currentFile++  
            $currentLines = 0  
        }  
    }  
}  
finally {  
    # 确保关闭最后一个文件  
    if ($writer -ne $null -and !$writer.BaseStream.IsClosed) {  
        $writer.Close()  
        $writer.Dispose()  
    }  
  
    $reader.Close()  
    $reader.Dispose()  
}  
  
echo "Done."