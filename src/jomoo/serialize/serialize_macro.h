#define register_class_1( object, member0 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_1( object, member0, member_type0 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_2( object, member0, member1 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_2( object, member0, member_type0, member1, member_type1 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_3( object, member0, member1, member2 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_3( object, member0, member_type0, member1, member_type1, member2, member_type2 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_4( object, member0, member1, member2, member3 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_4( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_5( object, member0, member1, member2, member3, member4 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_5( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_6( object, member0, member1, member2, member3, member4, member5 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_6( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_7( object, member0, member1, member2, member3, member4, member5, member6 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_7( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_8( object, member0, member1, member2, member3, member4, member5, member6, member7 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_8( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_9( object, member0, member1, member2, member3, member4, member5, member6, member7, member8 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_9( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_10( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_10( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_11( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && serialize(writer, context, s1.##member10, #member10) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && deserialize(reader, context, s1.##member10, #member10) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_11( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && serialize_##member_type10(writer, context, s1.##member10, #member10) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && deserialize_##member_type10(reader, context, s1.##member10, #member10) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_12( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && serialize(writer, context, s1.##member10, #member10) \
  && serialize(writer, context, s1.##member11, #member11) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && deserialize(reader, context, s1.##member10, #member10) \
  && deserialize(reader, context, s1.##member11, #member11) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_12( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && serialize_##member_type10(writer, context, s1.##member10, #member10) \
  && serialize_##member_type11(writer, context, s1.##member11, #member11) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && deserialize_##member_type10(reader, context, s1.##member10, #member10) \
  && deserialize_##member_type11(reader, context, s1.##member11, #member11) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_13( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && serialize(writer, context, s1.##member10, #member10) \
  && serialize(writer, context, s1.##member11, #member11) \
  && serialize(writer, context, s1.##member12, #member12) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && deserialize(reader, context, s1.##member10, #member10) \
  && deserialize(reader, context, s1.##member11, #member11) \
  && deserialize(reader, context, s1.##member12, #member12) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_13( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && serialize_##member_type10(writer, context, s1.##member10, #member10) \
  && serialize_##member_type11(writer, context, s1.##member11, #member11) \
  && serialize_##member_type12(writer, context, s1.##member12, #member12) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && deserialize_##member_type10(reader, context, s1.##member10, #member10) \
  && deserialize_##member_type11(reader, context, s1.##member11, #member11) \
  && deserialize_##member_type12(reader, context, s1.##member12, #member12) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_14( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && serialize(writer, context, s1.##member10, #member10) \
  && serialize(writer, context, s1.##member11, #member11) \
  && serialize(writer, context, s1.##member12, #member12) \
  && serialize(writer, context, s1.##member13, #member13) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && deserialize(reader, context, s1.##member10, #member10) \
  && deserialize(reader, context, s1.##member11, #member11) \
  && deserialize(reader, context, s1.##member12, #member12) \
  && deserialize(reader, context, s1.##member13, #member13) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_14( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && serialize_##member_type10(writer, context, s1.##member10, #member10) \
  && serialize_##member_type11(writer, context, s1.##member11, #member11) \
  && serialize_##member_type12(writer, context, s1.##member12, #member12) \
  && serialize_##member_type13(writer, context, s1.##member13, #member13) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && deserialize_##member_type10(reader, context, s1.##member10, #member10) \
  && deserialize_##member_type11(reader, context, s1.##member11, #member11) \
  && deserialize_##member_type12(reader, context, s1.##member12, #member12) \
  && deserialize_##member_type13(reader, context, s1.##member13, #member13) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_15( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && serialize(writer, context, s1.##member10, #member10) \
  && serialize(writer, context, s1.##member11, #member11) \
  && serialize(writer, context, s1.##member12, #member12) \
  && serialize(writer, context, s1.##member13, #member13) \
  && serialize(writer, context, s1.##member14, #member14) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && deserialize(reader, context, s1.##member10, #member10) \
  && deserialize(reader, context, s1.##member11, #member11) \
  && deserialize(reader, context, s1.##member12, #member12) \
  && deserialize(reader, context, s1.##member13, #member13) \
  && deserialize(reader, context, s1.##member14, #member14) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_15( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && serialize_##member_type10(writer, context, s1.##member10, #member10) \
  && serialize_##member_type11(writer, context, s1.##member11, #member11) \
  && serialize_##member_type12(writer, context, s1.##member12, #member12) \
  && serialize_##member_type13(writer, context, s1.##member13, #member13) \
  && serialize_##member_type14(writer, context, s1.##member14, #member14) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && deserialize_##member_type10(reader, context, s1.##member10, #member10) \
  && deserialize_##member_type11(reader, context, s1.##member11, #member11) \
  && deserialize_##member_type12(reader, context, s1.##member12, #member12) \
  && deserialize_##member_type13(reader, context, s1.##member13, #member13) \
  && deserialize_##member_type14(reader, context, s1.##member14, #member14) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_16( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14, member15 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && serialize(writer, context, s1.##member10, #member10) \
  && serialize(writer, context, s1.##member11, #member11) \
  && serialize(writer, context, s1.##member12, #member12) \
  && serialize(writer, context, s1.##member13, #member13) \
  && serialize(writer, context, s1.##member14, #member14) \
  && serialize(writer, context, s1.##member15, #member15) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && deserialize(reader, context, s1.##member10, #member10) \
  && deserialize(reader, context, s1.##member11, #member11) \
  && deserialize(reader, context, s1.##member12, #member12) \
  && deserialize(reader, context, s1.##member13, #member13) \
  && deserialize(reader, context, s1.##member14, #member14) \
  && deserialize(reader, context, s1.##member15, #member15) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_16( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14, member15, member_type15 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && serialize_##member_type10(writer, context, s1.##member10, #member10) \
  && serialize_##member_type11(writer, context, s1.##member11, #member11) \
  && serialize_##member_type12(writer, context, s1.##member12, #member12) \
  && serialize_##member_type13(writer, context, s1.##member13, #member13) \
  && serialize_##member_type14(writer, context, s1.##member14, #member14) \
  && serialize_##member_type15(writer, context, s1.##member15, #member15) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && deserialize_##member_type10(reader, context, s1.##member10, #member10) \
  && deserialize_##member_type11(reader, context, s1.##member11, #member11) \
  && deserialize_##member_type12(reader, context, s1.##member12, #member12) \
  && deserialize_##member_type13(reader, context, s1.##member13, #member13) \
  && deserialize_##member_type14(reader, context, s1.##member14, #member14) \
  && deserialize_##member_type15(reader, context, s1.##member15, #member15) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_17( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14, member15, member16 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && serialize(writer, context, s1.##member10, #member10) \
  && serialize(writer, context, s1.##member11, #member11) \
  && serialize(writer, context, s1.##member12, #member12) \
  && serialize(writer, context, s1.##member13, #member13) \
  && serialize(writer, context, s1.##member14, #member14) \
  && serialize(writer, context, s1.##member15, #member15) \
  && serialize(writer, context, s1.##member16, #member16) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && deserialize(reader, context, s1.##member10, #member10) \
  && deserialize(reader, context, s1.##member11, #member11) \
  && deserialize(reader, context, s1.##member12, #member12) \
  && deserialize(reader, context, s1.##member13, #member13) \
  && deserialize(reader, context, s1.##member14, #member14) \
  && deserialize(reader, context, s1.##member15, #member15) \
  && deserialize(reader, context, s1.##member16, #member16) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_17( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14, member15, member_type15, member16, member_type16 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && serialize_##member_type10(writer, context, s1.##member10, #member10) \
  && serialize_##member_type11(writer, context, s1.##member11, #member11) \
  && serialize_##member_type12(writer, context, s1.##member12, #member12) \
  && serialize_##member_type13(writer, context, s1.##member13, #member13) \
  && serialize_##member_type14(writer, context, s1.##member14, #member14) \
  && serialize_##member_type15(writer, context, s1.##member15, #member15) \
  && serialize_##member_type16(writer, context, s1.##member16, #member16) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && deserialize_##member_type10(reader, context, s1.##member10, #member10) \
  && deserialize_##member_type11(reader, context, s1.##member11, #member11) \
  && deserialize_##member_type12(reader, context, s1.##member12, #member12) \
  && deserialize_##member_type13(reader, context, s1.##member13, #member13) \
  && deserialize_##member_type14(reader, context, s1.##member14, #member14) \
  && deserialize_##member_type15(reader, context, s1.##member15, #member15) \
  && deserialize_##member_type16(reader, context, s1.##member16, #member16) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_18( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14, member15, member16, member17 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && serialize(writer, context, s1.##member10, #member10) \
  && serialize(writer, context, s1.##member11, #member11) \
  && serialize(writer, context, s1.##member12, #member12) \
  && serialize(writer, context, s1.##member13, #member13) \
  && serialize(writer, context, s1.##member14, #member14) \
  && serialize(writer, context, s1.##member15, #member15) \
  && serialize(writer, context, s1.##member16, #member16) \
  && serialize(writer, context, s1.##member17, #member17) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && deserialize(reader, context, s1.##member10, #member10) \
  && deserialize(reader, context, s1.##member11, #member11) \
  && deserialize(reader, context, s1.##member12, #member12) \
  && deserialize(reader, context, s1.##member13, #member13) \
  && deserialize(reader, context, s1.##member14, #member14) \
  && deserialize(reader, context, s1.##member15, #member15) \
  && deserialize(reader, context, s1.##member16, #member16) \
  && deserialize(reader, context, s1.##member17, #member17) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_18( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14, member15, member_type15, member16, member_type16, member17, member_type17 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && serialize_##member_type10(writer, context, s1.##member10, #member10) \
  && serialize_##member_type11(writer, context, s1.##member11, #member11) \
  && serialize_##member_type12(writer, context, s1.##member12, #member12) \
  && serialize_##member_type13(writer, context, s1.##member13, #member13) \
  && serialize_##member_type14(writer, context, s1.##member14, #member14) \
  && serialize_##member_type15(writer, context, s1.##member15, #member15) \
  && serialize_##member_type16(writer, context, s1.##member16, #member16) \
  && serialize_##member_type17(writer, context, s1.##member17, #member17) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && deserialize_##member_type10(reader, context, s1.##member10, #member10) \
  && deserialize_##member_type11(reader, context, s1.##member11, #member11) \
  && deserialize_##member_type12(reader, context, s1.##member12, #member12) \
  && deserialize_##member_type13(reader, context, s1.##member13, #member13) \
  && deserialize_##member_type14(reader, context, s1.##member14, #member14) \
  && deserialize_##member_type15(reader, context, s1.##member15, #member15) \
  && deserialize_##member_type16(reader, context, s1.##member16, #member16) \
  && deserialize_##member_type17(reader, context, s1.##member17, #member17) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_19( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14, member15, member16, member17, member18 ) \
inline bool serialize_##object(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize(writer, context, s1.##member0, #member0) \
  && serialize(writer, context, s1.##member1, #member1) \
  && serialize(writer, context, s1.##member2, #member2) \
  && serialize(writer, context, s1.##member3, #member3) \
  && serialize(writer, context, s1.##member4, #member4) \
  && serialize(writer, context, s1.##member5, #member5) \
  && serialize(writer, context, s1.##member6, #member6) \
  && serialize(writer, context, s1.##member7, #member7) \
  && serialize(writer, context, s1.##member8, #member8) \
  && serialize(writer, context, s1.##member9, #member9) \
  && serialize(writer, context, s1.##member10, #member10) \
  && serialize(writer, context, s1.##member11, #member11) \
  && serialize(writer, context, s1.##member12, #member12) \
  && serialize(writer, context, s1.##member13, #member13) \
  && serialize(writer, context, s1.##member14, #member14) \
  && serialize(writer, context, s1.##member15, #member15) \
  && serialize(writer, context, s1.##member16, #member16) \
  && serialize(writer, context, s1.##member17, #member17) \
  && serialize(writer, context, s1.##member18, #member18) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize(reader, context, s1.##member0, #member0) \
  && deserialize(reader, context, s1.##member1, #member1) \
  && deserialize(reader, context, s1.##member2, #member2) \
  && deserialize(reader, context, s1.##member3, #member3) \
  && deserialize(reader, context, s1.##member4, #member4) \
  && deserialize(reader, context, s1.##member5, #member5) \
  && deserialize(reader, context, s1.##member6, #member6) \
  && deserialize(reader, context, s1.##member7, #member7) \
  && deserialize(reader, context, s1.##member8, #member8) \
  && deserialize(reader, context, s1.##member9, #member9) \
  && deserialize(reader, context, s1.##member10, #member10) \
  && deserialize(reader, context, s1.##member11, #member11) \
  && deserialize(reader, context, s1.##member12, #member12) \
  && deserialize(reader, context, s1.##member13, #member13) \
  && deserialize(reader, context, s1.##member14, #member14) \
  && deserialize(reader, context, s1.##member15, #member15) \
  && deserialize(reader, context, s1.##member16, #member16) \
  && deserialize(reader, context, s1.##member17, #member17) \
  && deserialize(reader, context, s1.##member18, #member18) \
  && reader.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

#define register_class_with_type_19( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14, member15, member_type15, member16, member_type16, member17, member_type17, member18, member_type18 ) \
inline bool serialize_##object( _jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return writer.open( context, #object, name) \
  && serialize_##member_type0(writer, context, s1.##member0, #member0) \
  && serialize_##member_type1(writer, context, s1.##member1, #member1) \
  && serialize_##member_type2(writer, context, s1.##member2, #member2) \
  && serialize_##member_type3(writer, context, s1.##member3, #member3) \
  && serialize_##member_type4(writer, context, s1.##member4, #member4) \
  && serialize_##member_type5(writer, context, s1.##member5, #member5) \
  && serialize_##member_type6(writer, context, s1.##member6, #member6) \
  && serialize_##member_type7(writer, context, s1.##member7, #member7) \
  && serialize_##member_type8(writer, context, s1.##member8, #member8) \
  && serialize_##member_type9(writer, context, s1.##member9, #member9) \
  && serialize_##member_type10(writer, context, s1.##member10, #member10) \
  && serialize_##member_type11(writer, context, s1.##member11, #member11) \
  && serialize_##member_type12(writer, context, s1.##member12, #member12) \
  && serialize_##member_type13(writer, context, s1.##member13, #member13) \
  && serialize_##member_type14(writer, context, s1.##member14, #member14) \
  && serialize_##member_type15(writer, context, s1.##member15, #member15) \
  && serialize_##member_type16(writer, context, s1.##member16, #member16) \
  && serialize_##member_type17(writer, context, s1.##member17, #member17) \
  && serialize_##member_type18(writer, context, s1.##member18, #member18) \
  && writer.close( context); } \
inline bool serialize(_jomoo_serializing serialize_writer& writer, _jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(writer, context, s1, name);} \
inline bool deserialize_##object(_jomoo_serializing serialize_reader& reader, _jomoo_serializing serialize_context& context, object & s1, const tchar* name=0) \
{ return reader.open( context, #object, name) \
  && deserialize_##member_type0(reader, context, s1.##member0, #member0) \
  && deserialize_##member_type1(reader, context, s1.##member1, #member1) \
  && deserialize_##member_type2(reader, context, s1.##member2, #member2) \
  && deserialize_##member_type3(reader, context, s1.##member3, #member3) \
  && deserialize_##member_type4(reader, context, s1.##member4, #member4) \
  && deserialize_##member_type5(reader, context, s1.##member5, #member5) \
  && deserialize_##member_type6(reader, context, s1.##member6, #member6) \
  && deserialize_##member_type7(reader, context, s1.##member7, #member7) \
  && deserialize_##member_type8(reader, context, s1.##member8, #member8) \
  && deserialize_##member_type9(reader, context, s1.##member9, #member9) \
  && deserialize_##member_type10(reader, context, s1.##member10, #member10) \
  && deserialize_##member_type11(reader, context, s1.##member11, #member11) \
  && deserialize_##member_type12(reader, context, s1.##member12, #member12) \
  && deserialize_##member_type13(reader, context, s1.##member13, #member13) \
  && deserialize_##member_type14(reader, context, s1.##member14, #member14) \
  && deserialize_##member_type15(reader, context, s1.##member15, #member15) \
  && deserialize_##member_type16(reader, context, s1.##member16, #member16) \
  && deserialize_##member_type17(reader, context, s1.##member17, #member17) \
  && deserialize_##member_type18(reader, context, s1.##member18, #member18) \
  && writer.close(context); } \
inline bool deserialize(_jomoo_serializing serialize_reader& reader,_jomoo_serializing serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(reader, context, s1, name);}

