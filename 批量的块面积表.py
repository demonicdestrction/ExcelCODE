import arcpy 
def deletable_field_names(file_name,field):
    fc_to_update = file_name
    field_to_keep = field  
    all_fields = [f.name for f in arcpy.ListFields(fc_to_update)]  
    non_deletable_fields = ['FID', 'OID','ObjectID', 'Shape', 'Shape_Length', 'Shape_Area']
  
    deletable_fields = [field for field in all_fields if field not in field_to_keep and field not in non_deletable_fields]   
    
    arcpy.management.DeleteField(file_name,deletable_fields) 
#cad转地理数据库
arcpy.env.workspace = r"D:\GIS"   
dwg_name = "D:\GIS\岭头.dwg"
gdb_name = "D:\GIS\数据库.gdb"
arcpy.conversion.CADToGeodatabase(dwg_name, gdb_name, "村数据","3000")

arcpy.env.workspace = r"D:\GIS\数据库.gdb"

annotation_fc = "Annotation"  # 转换后的注记要素类  
polygon_fc = "Polygon"        # 转换后的面要素类 

output_fc = ""

point1 = "幢号"
point2 = "房屋属性点"
point3 = "承租方点"

layer_name1 = "房屋面"
layer_name2 = "外扩线面"
layer_name3 = "物业面"

where_clause1 = "Layer = '幢号'"
where_clause2 = "Layer = 'JMD'"
where_clause3 = "Layer = '承租方'"
where_clause4 = "Layer = 'JMD' OR Layer = 'ASSIST'"
where_clause5 = "Layer = '外扩线'"
where_clause6 = "Layer = 'JZD_物业'"

arcpy.management.FeatureToPoint(annotation_fc, point1, "CENTROID")
arcpy.management.FeatureToPoint(annotation_fc, point2, "CENTROID")
arcpy.management.FeatureToPoint(annotation_fc, point3, "CENTROID")

#arcpy.MakeFeatureLayer_management(annotation_fc, point1) #可是dwg中的注记
#arcpy.MakeFeatureLayer_management(annotation_fc, point2)
#arcpy.MakeFeatureLayer_management(annotation_fc, point3) 
 
arcpy.MakeFeatureLayer_management(polygon_fc, layer_name1)
arcpy.MakeFeatureLayer_management(polygon_fc, layer_name2)
arcpy.MakeFeatureLayer_management(polygon_fc, layer_name3)  

arcpy.management.SelectLayerByAttribute(point1, "NEW_SELECTION", where_clause1)
arcpy.management.SelectLayerByAttribute(point2, "NEW_SELECTION", where_clause2)
arcpy.management.SelectLayerByAttribute(point3, "NEW_SELECTION", where_clause3)
arcpy.management.SelectLayerByAttribute(layer_name1, "NEW_SELECTION", where_clause4)
arcpy.management.SelectLayerByAttribute(layer_name2, "NEW_SELECTION", where_clause5)
arcpy.management.SelectLayerByAttribute(layer_name3, "NEW_SELECTION", where_clause6)

arcpy.env.workspace = r"D:\GIS\数据"

output_fc1 = "物业带名称"
output_fc2 = "栋号"
output_fc3 = "外扩线带栋号"
output_fc4 = "房屋带栋号"
output_fc5 = "房屋1" #房屋连接属性点第一次
output_fc6 = "房屋2" #房屋连接属性点第二次（一对多连接）

arcpy.SpatialJoin_analysis(layer_name3, point3, output_fc1, 
                           join_operation = "JOIN_ONE_TO_ONE",match_option = "INTERSECT")
arcpy.SpatialJoin_analysis(point1, output_fc1, output_fc2, 
                           join_operation = "JOIN_ONE_TO_ONE",match_option = "INTERSECT")
                           
arcpy.management.AddField(output_fc2, "dh", "TEXT", "", "", "100")
arcpy.management.CalculateField(output_fc2, "dh", 
                                '[Text_1]&"-"&[Text]', "VB") 
deletable_field_names(output_fc2, ["dh"]) 
                               
arcpy.SpatialJoin_analysis(layer_name2, output_fc2, output_fc3, 
                           join_operation = "JOIN_ONE_TO_ONE",match_option = "INTERSECT") 
arcpy.SpatialJoin_analysis(layer_name1, output_fc3, output_fc4, 
                           join_operation = "JOIN_ONE_TO_ONE",match_option = "WITHIN_CLEMENTINI")
arcpy.SpatialJoin_analysis(output_fc4, point2, output_fc5, 
                           join_operation = "JOIN_ONE_TO_ONE",match_option = "INTERSECT")
deletable_field_names(output_fc5, ["TextString", "TextString_1","dh", "Join_Count", "Join_Cou_1"])                              
arcpy.SpatialJoin_analysis(output_fc5, point2, output_fc6, 
                           join_operation = "JOIN_ONE_TO_MANY",match_option = "INTERSECT") 
                        
deletable_field_names(output_fc6, ["TextString","TextStri_1","dh","Join_Cou_2"])
arcpy.management.AddGeometryAttributes(output_fc6, "AREA","","SQUARE_METERS")

#arcpy.management.CalculateGeometryAttributes()
arcpy.conversion.TableToExcel(output_fc6, "面积表.xls")






