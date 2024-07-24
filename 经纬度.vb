
Function InsertFiveRowsAfterSpecificRow(rng As Range)
    Dim hang As Integer
    Dim ws As Worksheet
    
    Dim sheetName As String
    Dim startRow As Long
    Dim Column As Long
    '获取单元格的相关信息
    sheetName = rng.Parent.Name
    startRow = rng.Row
    Column = rng.Column
    
    'startRow = 1 ' 指定起始行为第1行
    'C = "F"
    Set ws = ThisWorkbook.Sheets(sheetName) ' 指定工作表
    hang = ws.Cells(startRow, Column).Value '获取开始单元格的值
    
    
    For i = 1 To 5000
        If hang = 0 Then
            startRow = startRow + 1
            hang = ws.Cells(startRow, Column).Value
        Else
            inster ws, startRow, hang
            startRow = startRow + hang
            hang = ws.Cells(startRow, Column).Value
        End If
    Next
End Function
    
Function inster(ws As Worksheet, startRow As Long, hang As Integer)
    Dim i As Long
    'Set ws = ThisWorkbook.Sheets("Sheet2") ' 指定工作表为Sheet1
    For i = 1 To hang - 1
        ws.Rows(startRow + i & ":" & startRow + i).Insert Shift:=xlDown
    Next i
End Function




Function InsertRowsBasedOnDifference(rng As Range)
    Dim ws As Worksheet
    
    Dim sheetName As String
    Dim startRow As Long
    Dim Column As Long
    
    Dim fnumber As Integer
    Dim snumber As Integer
    Dim Row As Long
    Dim rowsToInsert As Integer
    
    '获取单元格的相关信息
    sheetName = rng.Parent.Name
    startRow = rng.Row
    Column = rng.Column
    
    
    'sheetName = "Sheet2"
    'startRow = 1
    'Column = 1
    
    Set ws = ThisWorkbook.Sheets(sheetName)
      
    Row = startRow
    fnumber = ws.Cells(Row, Column).Value
    snumber = ws.Cells(Row + 1, Column).Value
    'ThisWorkbook.Sheets("sheet2").Cells(Row, 1)Value = 1
    Dim i As Integer
    For i = 1 To 4000
        ThisWorkbook.Sheets("sheet3").Cells(Row, 1).Value = fnumber
        'If Row + 1 > ws.Cells(ws.Rows.Count, Column).End(xlUp).Row Then
            'Exit For ' 如果到了最后一行，则退出循环
        'End If
          
        If snumber - fnumber > 1 Then
            rowsToInsert = snumber - fnumber
            InsertRows ws, Row, rowsToInsert
            Row = Row + rowsToInsert ' 更新当前行位置
        End If
          
        Row = Row + 1 ' 无论如何都移动到下一行
          
        ' 检查是否到达最后一行或超出范围
        'If Row + 1 > ws.Cells(ws.Rows.Count, Column).End(xlUp).Row Then
            'Exit For
        'End If
          
        fnumber = ws.Cells(Row, Column).Value
        snumber = ws.Cells(Row + 1, Column).Value
    Next i
End Function

Function InsertRows(ws As Worksheet, startRow As Long, hang As Integer)
    Dim i As Long
    'Dim ws As Worksheet
    'Set ws = ThisWorkbook.Sheets("Sheet2") ' 如果这里是指Sheet2，请确认是否正确
    For i = 1 To hang - 1
        ws.Rows(startRow + 1).Insert Shift:=xlDown
    Next i
End Function

Sub getAll()
    
      
    ' 定义 Range 变量
    Dim rng1 As Range
    Dim rng2 As Range
      
    ' 正确设置 Range 变量
    ' 注意：这里使用了 Set 关键字来分配对象引用
	'对sheet2中F1开始的F列，根据单元格的值插入减一行
    Set rng1 = ThisWorkbook.Sheets("Sheet2").Range("F1:F1") 
	
	'处理Sheet3中E1开始的E列序数（1234679）序数断开的情况
	'差几个插入多少行
    Set rng2 = ThisWorkbook.Sheets("Sheet3").Range("E1:E1") 
      
   
    InsertFiveRowsAfterSpecificRow rng1
    InsertRowsBasedOnDifference rng2
      
End Sub



