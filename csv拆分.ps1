$sourceFile = "aaa.csv"  
$maxLines = 3000  
$currentFile = 1  
$currentLines = 0  
  
$outputFileBase = "output"  

  
$reader = New-Object System.IO.StreamReader($sourceFile)  
  
try {  
    while (!$reader.EndOfStream) {  
        $line = $reader.ReadLine()  
  
        # �����Ҫ���������ļ�  
        if ($currentLines -eq 0) {  
            $outputFile = [System.IO.Path]::Combine($outputDir, "$outputFileBase$currentFile.csv")  
            $writer = New-Object System.IO.StreamWriter($outputFile)  
        }  
  
        $writer.WriteLine($line)  
        $currentLines++  
  
        # ����Ƿ���Ҫ��ʼ���ļ�  
        if ($currentLines -ge $maxLines) {  
            $writer.Close()  
            $writer.Dispose()  
            $currentFile++  
            $currentLines = 0  
        }  
    }  
}  
finally {  
    # ȷ���ر����һ���ļ�  
    if ($writer -ne $null -and !$writer.BaseStream.IsClosed) {  
        $writer.Close()  
        $writer.Dispose()  
    }  
  
    $reader.Close()  
    $reader.Dispose()  
}  
  
echo "Done."