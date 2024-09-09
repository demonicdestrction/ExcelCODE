#空间连接
import arcpy  
def deletable_field_names(file_name,field):
    fc_to_update = file_name
    field_to_keep = field  
    all_fields = [f.name for f in arcpy.ListFields(fc_to_update)]  
    non_deletable_fields = ['FID', 'OID','ObjectID', 'Shape', 'Shape_Length', 'Shape_Area']
  
    deletable_fields = [field for field in all_fields if field not in field_to_keep and field not in non_deletable_fields]   
    
    arcpy.management.DeleteField(file_name,deletable_fields)
     

arcpy.env.workspace = r"D:\GIS\11.dwg"  
annotation_fc = "Annotation"  # 转换后的注记要素类  
polygon_fc = "Polygon"        # 转换后的面要素类 
output_fc = "D:\GIS\结果" 

layer_name1 = "图层1"
layer_name2 = "图层2"

arcpy.MakeFeatureLayer_management(annotation_fc, layer_name1)
arcpy.MakeFeatureLayer_management(polygon_fc, layer_name2) 
  
where_clause1 = "Layer = '栋号'"
where_clause2 = "Layer = 'JMD'"

arcpy.management.SelectLayerByAttribute(layer_name1, "NEW_SELECTION", where_clause1)
arcpy.SelectLayerByAttribute_management(layer_name2, "NEW_SELECTION", where_clause2)

output_fc = "D:\GIS\结果"
arcpy.SpatialJoin_analysis(layer_name2, layer_name1, output_fc, 
                           join_operation = "JOIN_ONE_TO_ONE",match_option = "INTERSECT")
arcpy.FeatureVerticesToPoints_management("D:\GIS\结果.shp","D:\GIS\点结果", "ALL") 

arcpy.env.workspace = r"D:\GIS" 
 
deletable_field_names("D:\GIS\点结果.shp", ["Layer", "TextString"])

arcpy.AddXY_management("点结果") 

arcpy.conversion.TableToExcel("点结果", r"D:\GIS\经纬度表1.xls")

#arcpy.management.DeleteField("D:\GIS\点结果.shp", ["Layer", "Text"], "KEEP_FIELDS")

