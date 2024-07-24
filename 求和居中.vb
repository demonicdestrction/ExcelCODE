
Function TestSumRange1(rng As Range)
    Dim rowCount As Integer
    Dim firstrow As Integer
    Dim colNum As Integer
    Dim sheetName As String
    
    Dim myArray() As Variant
    rowCount = rng.Rows.Count
    firstrow = rng.Row
    colNum = rng.Column
    sheetName = rng.Parent.Name
    ReDim myArray(1 To rowCount)
    '动态定义数组
    
    Dim max As Integer
    Dim min As Integer
    max = rowCount
    min = firstrow
    
    Dim A As String
    Dim B As String
    Dim C As String
    A = ColumnNumberToLetter(colNum)
    B = ColumnNumberToLetter(colNum + 1)
    C = ColumnNumberToLetter(colNum + 2)
    
    Dim i As Integer
    Dim rng2 As Range
    Dim j As Integer
    Dim k As Integer
    ' 初始化数组，这里只是简单地假设数组包含 1 到 15 的整数（实际上从工作表读取）
    ' 注意：这里我们并没有真正从工作表读取，只是为了示例
    
    For i = min + 1 To max
        myArray(i - min) = 0
         ' 假设是 1 到 15，而不是从工作表读取
        ' 如果确实需要从工作表读取，则取消下一行的注释
        ' myArray(i) = ThisWorkbook.Sheets("Sheet1").Range(A & i).Value
    Next i
    
    For i = min + 1 To max
        myArray(i - min) = ThisWorkbook.Sheets(sheetName).Range(A & i).Value
         ' 假设是 1 到 15，而不是从工作表读取
        ' 如果确实需要从工作表读取，则取消下一行的注释
        ' myArray(i) = ThisWorkbook.Sheets("Sheet1").Range(A & i).Value
    Next i
    j = min
    k = min 
    ' 遍历数组，根据条件计算和
    For i = min + 1 To max
        If myArray(i - min) = 1 Then
            Set rng2 = ThisWorkbook.Sheets(sheetName).Range(B & j & ":" & B & k) ' 假设只计算一行
            'ThisWorkbook.Sheets("Sheet2").Range("C" & i).Value = SumRange(rng2)
            
                 With ThisWorkbook.Sheets(sheetName).Range(C & j & ":" & C & k)
                    .Merge ' 合并单元格
                    .Value = SumRange(rng2)
                End With
            
            j = i
            k = i
        ElseIf myArray(i - min) = 0 Then
            Set rng2 = ThisWorkbook.Sheets(sheetName).Range(B & j & ":" & B & k) ' 假设只计算一行
            'ThisWorkbook.Sheets("Sheet2").Range("C" & i).Value = SumRange(rng2)
            
                 With ThisWorkbook.Sheets(sheetName).Range(C & j & ":" & C & k)
                    .Merge ' 合并单元格
                    .Value = SumRange(rng2)
                End With
            
            j = i
            k = i
        Else
            k = i
        End If
    Next i
      
    ' 注意：我们没有使用 sum 变量，因为它在您的原始代码中没有正确设置或更新
    ' 如果需要显示某个特定的和（比如所有 B 列的和，不包括与 1 对应的行），则需要额外的逻辑
    ThisWorkbook.Sheets(sheetName).Columns(C).Replace What:=0, Replacement:="", LookAt:=xlWhole, _
        SearchOrder:=xlByRows, MatchCase:=False
End Function
'列号转字母
Function ColumnNumberToLetter(ByVal colNum As Long) As String
    Dim div As Long
    Dim modResult As Integer
    Dim colLetter As String
      
    ' 确保列号大于0
    If colNum <= 0 Then
        ColumnNumberToLetter = "Invalid column number"
        Exit Function
    End If
      
    ' 从列号的最低位开始转换
    colLetter = ""
    Do While colNum > 0
        modResult = colNum Mod 26
          
        ' 如果modResult为0，则使用'Z'而不是''（因为Excel列在26的倍数时不会跳过）
        If modResult = 0 Then
            modResult = 26
            colNum = colNum \ 26 - 1
        Else
            colNum = colNum \ 26
        End If
          
        ' 将当前字母添加到结果字符串的前面
        colLetter = Chr(modResult + 64) & colLetter
    Loop
      
    ' 返回转换后的列字母
    ColumnNumberToLetter = colLetter
End Function
Function SumRange(rng As Range) As Double
    Dim sumResult As Double
      
    ' 使用 Application.Sum 来避免错误值导致的问题
    sumResult = Application.sum(rng)
      
    ' 直接返回结果
    SumRange = sumResult
End Function
'main
'假如输入的是A1：A100（值是1，2，3，1，2，1,1）
'获取B1：B100的值，求和居中（C1:C3，C4:C5,C1:C3,C6）
'解决序列求和问题
Sub Sum2()
    Dim currentSheetName As String
      
    ' 获取当前激活工作表的名称
    currentSheetName = ActiveSheet.Name
    
    TestSumRange1 ThisWorkbook.Sheets(currentSheetName).Range("c7:c210") ' 注意没有括号
End Sub