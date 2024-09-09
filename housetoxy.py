import arcpy  
def deletable_field_names(file_name,field):
    fc_to_update = file_name
    field_to_keep = field  
    all_fields = [f.name for f in arcpy.ListFields(fc_to_update)]  
    non_deletable_fields = ['FID', 'OID','ObjectID', 'Shape', 'Shape_Length', 'Shape_Area']
  
    deletable_fields = [field for field in all_fields if field not in field_to_keep and field not in non_deletable_fields]   
    
    arcpy.management.DeleteField(file_name,deletable_fields)
def house_to_xy(workspace, output_file_name):
    arcpy.env.workspace = workspace
    
    annotation_fc = "Annotation"  # 转换后的注记要素类  
    polygon_fc = "Polygon"        # 转换后的面要素类 

    layer_name1 = "栋号注记"
    layer_name2 = "外扩线"
    where_clause1 = "Layer = '栋号'"
    where_clause2 = "Layer = '外扩线'"
    
    arcpy.MakeFeatureLayer_management(annotation_fc, layer_name1)
    arcpy.MakeFeatureLayer_management(polygon_fc, layer_name2) 
  
    arcpy.management.SelectLayerByAttribute(layer_name1, "NEW_SELECTION", where_clause1)
    arcpy.SelectLayerByAttribute_management(layer_name2, "NEW_SELECTION", where_clause2)

    arcpy.env.workspace = output_file_name
    output_fc = "外扩线带栋号面"
    output_fc1 = "外扩线带栋号点"
    output_excel = "经纬度表.xls"
    
    arcpy.SpatialJoin_analysis(layer_name2, layer_name1, output_fc, 
                                join_operation = "JOIN_ONE_TO_ONE",match_option = "INTERSECT")                  
    arcpy.FeatureVerticesToPoints_management(output_fc, output_fc1, "ALL") 
    deletable_field_names(output_fc1, ["Layer", "TextString"])
    
    output_point1 = "转坐标后点"
    output_point2 = output_file_name + "\转坐标后点.shp"
    arcpy.Project_management(output_point, output_point1, arcpy.SpatialReference(4490))
    #arcpy.AddGeometryAttributes_management(output_point1, "POINT_X_Y_Z_M") 
    arcpy.AddXY_management(output_point2) 
    arcpy.conversion.TableToExcel(output_point2, output_excel)

def house_to_xy1(workspace, output_file_name):

    arcpy.env.workspace = workspace
    annotation_fc = "Annotation"  # 转换后的注记要素类  
    polygon_fc = "Polygon"        # 转换后的面要素类 

    point1 = "幢号"
    point2 = "承租方点"

    layer_name1 = "外扩线面"
    layer_name2 = "物业面"

    where_clause1 = "Layer = '幢号'"
    where_clause2 = "Layer = 'JMD'"
    where_clause3 = "Layer = '承租方'"
    where_clause4 = "Layer = 'JMD' OR Layer = 'ASSIST'"
    where_clause5 = "Layer = '外扩线'"
    where_clause6 = "Layer = 'JZD_物业'"

    arcpy.MakeFeatureLayer_management(annotation_fc, point1) 
    arcpy.MakeFeatureLayer_management(annotation_fc, point2)
    
   
    arcpy.MakeFeatureLayer_management(polygon_fc, layer_name1)
    arcpy.MakeFeatureLayer_management(polygon_fc, layer_name2)  

    arcpy.management.SelectLayerByAttribute(point1, "NEW_SELECTION", where_clause1)
    arcpy.management.SelectLayerByAttribute(point2, "NEW_SELECTION", where_clause3)
    
    arcpy.management.SelectLayerByAttribute(layer_name1, "NEW_SELECTION", where_clause5)
    arcpy.management.SelectLayerByAttribute(layer_name2, "NEW_SELECTION", where_clause6)

    arcpy.env.workspace = output_file_name

    output_fc1 = "物业带名称"
    output_fc2 = "栋号"

    arcpy.SpatialJoin_analysis(layer_name2, point2, output_fc1, 
                            join_operation = "JOIN_ONE_TO_ONE",match_option = "INTERSECT")
    arcpy.SpatialJoin_analysis(point1, output_fc1, output_fc2, 
                            join_operation = "JOIN_ONE_TO_ONE",match_option = "INTERSECT")
                           
    arcpy.management.AddField(output_fc2, "dh", "TEXT", "", "", "100")
    arcpy.management.CalculateField(output_fc2, "dh", '[Text_1]&"-"&[Text]', "VB") 
    deletable_field_names(output_fc2, ["dh"])
    
    output_fc = "外扩线带栋号"
    output_point = "外扩线带栋号点"
    output_excel = "经纬度表.xls"
    
    arcpy.SpatialJoin_analysis(layer_name2, output_fc2, output_fc, 
                           join_operation = "JOIN_ONE_TO_ONE",match_option = "INTERSECT")
    arcpy.FeatureVerticesToPoints_management(output_fc, output_point, "ALL") 
    deletable_field_names(output_point, ["Layer", "dh"])
    
    output_point1 = "转坐标后点"
    output_point2 = output_file_name + "\转坐标后点.shp"
    arcpy.Project_management(output_point, output_point1, arcpy.SpatialReference(4490))
    #arcpy.AddGeometryAttributes_management(output_point1, "POINT_X_Y_Z_M") 
    arcpy.AddXY_management(output_point2) 
    arcpy.conversion.TableToExcel(output_point2, output_excel)
    
#house_to_xy1(workspace, output_file_name)，其一为dwg路径，后为存储数据的问价夹名   
#house_to_xy("D:\GIS\岭头.dwg","D:\GIS\结果")#标了栋号的
house_to_xy1("D:\GIS\岭头.dwg","D:\GIS\结果")#只有栋号只是是数字1,2,3的

 


