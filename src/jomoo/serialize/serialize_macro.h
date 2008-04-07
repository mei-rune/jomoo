#define register_class( object, member0 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && serialize(strm, context, s1.##member10, #member10) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && deserialize(strm, context, s1.##member10, #member10) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && serialize_##member_type10(strm, context, s1.##member10, #member10) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && deserialize_##member_type10(strm, context, s1.##member10, #member10) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && serialize(strm, context, s1.##member10, #member10) \
  && serialize(strm, context, s1.##member11, #member11) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && deserialize(strm, context, s1.##member10, #member10) \
  && deserialize(strm, context, s1.##member11, #member11) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && serialize_##member_type10(strm, context, s1.##member10, #member10) \
  && serialize_##member_type11(strm, context, s1.##member11, #member11) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && deserialize_##member_type10(strm, context, s1.##member10, #member10) \
  && deserialize_##member_type11(strm, context, s1.##member11, #member11) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && serialize(strm, context, s1.##member10, #member10) \
  && serialize(strm, context, s1.##member11, #member11) \
  && serialize(strm, context, s1.##member12, #member12) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && deserialize(strm, context, s1.##member10, #member10) \
  && deserialize(strm, context, s1.##member11, #member11) \
  && deserialize(strm, context, s1.##member12, #member12) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && serialize_##member_type10(strm, context, s1.##member10, #member10) \
  && serialize_##member_type11(strm, context, s1.##member11, #member11) \
  && serialize_##member_type12(strm, context, s1.##member12, #member12) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && deserialize_##member_type10(strm, context, s1.##member10, #member10) \
  && deserialize_##member_type11(strm, context, s1.##member11, #member11) \
  && deserialize_##member_type12(strm, context, s1.##member12, #member12) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && serialize(strm, context, s1.##member10, #member10) \
  && serialize(strm, context, s1.##member11, #member11) \
  && serialize(strm, context, s1.##member12, #member12) \
  && serialize(strm, context, s1.##member13, #member13) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && deserialize(strm, context, s1.##member10, #member10) \
  && deserialize(strm, context, s1.##member11, #member11) \
  && deserialize(strm, context, s1.##member12, #member12) \
  && deserialize(strm, context, s1.##member13, #member13) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && serialize_##member_type10(strm, context, s1.##member10, #member10) \
  && serialize_##member_type11(strm, context, s1.##member11, #member11) \
  && serialize_##member_type12(strm, context, s1.##member12, #member12) \
  && serialize_##member_type13(strm, context, s1.##member13, #member13) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && deserialize_##member_type10(strm, context, s1.##member10, #member10) \
  && deserialize_##member_type11(strm, context, s1.##member11, #member11) \
  && deserialize_##member_type12(strm, context, s1.##member12, #member12) \
  && deserialize_##member_type13(strm, context, s1.##member13, #member13) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && serialize(strm, context, s1.##member10, #member10) \
  && serialize(strm, context, s1.##member11, #member11) \
  && serialize(strm, context, s1.##member12, #member12) \
  && serialize(strm, context, s1.##member13, #member13) \
  && serialize(strm, context, s1.##member14, #member14) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && deserialize(strm, context, s1.##member10, #member10) \
  && deserialize(strm, context, s1.##member11, #member11) \
  && deserialize(strm, context, s1.##member12, #member12) \
  && deserialize(strm, context, s1.##member13, #member13) \
  && deserialize(strm, context, s1.##member14, #member14) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && serialize_##member_type10(strm, context, s1.##member10, #member10) \
  && serialize_##member_type11(strm, context, s1.##member11, #member11) \
  && serialize_##member_type12(strm, context, s1.##member12, #member12) \
  && serialize_##member_type13(strm, context, s1.##member13, #member13) \
  && serialize_##member_type14(strm, context, s1.##member14, #member14) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && deserialize_##member_type10(strm, context, s1.##member10, #member10) \
  && deserialize_##member_type11(strm, context, s1.##member11, #member11) \
  && deserialize_##member_type12(strm, context, s1.##member12, #member12) \
  && deserialize_##member_type13(strm, context, s1.##member13, #member13) \
  && deserialize_##member_type14(strm, context, s1.##member14, #member14) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14, member15 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && serialize(strm, context, s1.##member10, #member10) \
  && serialize(strm, context, s1.##member11, #member11) \
  && serialize(strm, context, s1.##member12, #member12) \
  && serialize(strm, context, s1.##member13, #member13) \
  && serialize(strm, context, s1.##member14, #member14) \
  && serialize(strm, context, s1.##member15, #member15) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && deserialize(strm, context, s1.##member10, #member10) \
  && deserialize(strm, context, s1.##member11, #member11) \
  && deserialize(strm, context, s1.##member12, #member12) \
  && deserialize(strm, context, s1.##member13, #member13) \
  && deserialize(strm, context, s1.##member14, #member14) \
  && deserialize(strm, context, s1.##member15, #member15) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14, member15, member_type15 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && serialize_##member_type10(strm, context, s1.##member10, #member10) \
  && serialize_##member_type11(strm, context, s1.##member11, #member11) \
  && serialize_##member_type12(strm, context, s1.##member12, #member12) \
  && serialize_##member_type13(strm, context, s1.##member13, #member13) \
  && serialize_##member_type14(strm, context, s1.##member14, #member14) \
  && serialize_##member_type15(strm, context, s1.##member15, #member15) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && deserialize_##member_type10(strm, context, s1.##member10, #member10) \
  && deserialize_##member_type11(strm, context, s1.##member11, #member11) \
  && deserialize_##member_type12(strm, context, s1.##member12, #member12) \
  && deserialize_##member_type13(strm, context, s1.##member13, #member13) \
  && deserialize_##member_type14(strm, context, s1.##member14, #member14) \
  && deserialize_##member_type15(strm, context, s1.##member15, #member15) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14, member15, member16 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && serialize(strm, context, s1.##member10, #member10) \
  && serialize(strm, context, s1.##member11, #member11) \
  && serialize(strm, context, s1.##member12, #member12) \
  && serialize(strm, context, s1.##member13, #member13) \
  && serialize(strm, context, s1.##member14, #member14) \
  && serialize(strm, context, s1.##member15, #member15) \
  && serialize(strm, context, s1.##member16, #member16) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && deserialize(strm, context, s1.##member10, #member10) \
  && deserialize(strm, context, s1.##member11, #member11) \
  && deserialize(strm, context, s1.##member12, #member12) \
  && deserialize(strm, context, s1.##member13, #member13) \
  && deserialize(strm, context, s1.##member14, #member14) \
  && deserialize(strm, context, s1.##member15, #member15) \
  && deserialize(strm, context, s1.##member16, #member16) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14, member15, member_type15, member16, member_type16 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && serialize_##member_type10(strm, context, s1.##member10, #member10) \
  && serialize_##member_type11(strm, context, s1.##member11, #member11) \
  && serialize_##member_type12(strm, context, s1.##member12, #member12) \
  && serialize_##member_type13(strm, context, s1.##member13, #member13) \
  && serialize_##member_type14(strm, context, s1.##member14, #member14) \
  && serialize_##member_type15(strm, context, s1.##member15, #member15) \
  && serialize_##member_type16(strm, context, s1.##member16, #member16) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && deserialize_##member_type10(strm, context, s1.##member10, #member10) \
  && deserialize_##member_type11(strm, context, s1.##member11, #member11) \
  && deserialize_##member_type12(strm, context, s1.##member12, #member12) \
  && deserialize_##member_type13(strm, context, s1.##member13, #member13) \
  && deserialize_##member_type14(strm, context, s1.##member14, #member14) \
  && deserialize_##member_type15(strm, context, s1.##member15, #member15) \
  && deserialize_##member_type16(strm, context, s1.##member16, #member16) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14, member15, member16, member17 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && serialize(strm, context, s1.##member10, #member10) \
  && serialize(strm, context, s1.##member11, #member11) \
  && serialize(strm, context, s1.##member12, #member12) \
  && serialize(strm, context, s1.##member13, #member13) \
  && serialize(strm, context, s1.##member14, #member14) \
  && serialize(strm, context, s1.##member15, #member15) \
  && serialize(strm, context, s1.##member16, #member16) \
  && serialize(strm, context, s1.##member17, #member17) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && deserialize(strm, context, s1.##member10, #member10) \
  && deserialize(strm, context, s1.##member11, #member11) \
  && deserialize(strm, context, s1.##member12, #member12) \
  && deserialize(strm, context, s1.##member13, #member13) \
  && deserialize(strm, context, s1.##member14, #member14) \
  && deserialize(strm, context, s1.##member15, #member15) \
  && deserialize(strm, context, s1.##member16, #member16) \
  && deserialize(strm, context, s1.##member17, #member17) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14, member15, member_type15, member16, member_type16, member17, member_type17 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && serialize_##member_type10(strm, context, s1.##member10, #member10) \
  && serialize_##member_type11(strm, context, s1.##member11, #member11) \
  && serialize_##member_type12(strm, context, s1.##member12, #member12) \
  && serialize_##member_type13(strm, context, s1.##member13, #member13) \
  && serialize_##member_type14(strm, context, s1.##member14, #member14) \
  && serialize_##member_type15(strm, context, s1.##member15, #member15) \
  && serialize_##member_type16(strm, context, s1.##member16, #member16) \
  && serialize_##member_type17(strm, context, s1.##member17, #member17) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && deserialize_##member_type10(strm, context, s1.##member10, #member10) \
  && deserialize_##member_type11(strm, context, s1.##member11, #member11) \
  && deserialize_##member_type12(strm, context, s1.##member12, #member12) \
  && deserialize_##member_type13(strm, context, s1.##member13, #member13) \
  && deserialize_##member_type14(strm, context, s1.##member14, #member14) \
  && deserialize_##member_type15(strm, context, s1.##member15, #member15) \
  && deserialize_##member_type16(strm, context, s1.##member16, #member16) \
  && deserialize_##member_type17(strm, context, s1.##member17, #member17) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class( object, member0, member1, member2, member3, member4, member5, member6, member7, member8, member9, member10, member11, member12, member13, member14, member15, member16, member17, member18 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize(strm, context, s1.##member0, #member0) \
  && serialize(strm, context, s1.##member1, #member1) \
  && serialize(strm, context, s1.##member2, #member2) \
  && serialize(strm, context, s1.##member3, #member3) \
  && serialize(strm, context, s1.##member4, #member4) \
  && serialize(strm, context, s1.##member5, #member5) \
  && serialize(strm, context, s1.##member6, #member6) \
  && serialize(strm, context, s1.##member7, #member7) \
  && serialize(strm, context, s1.##member8, #member8) \
  && serialize(strm, context, s1.##member9, #member9) \
  && serialize(strm, context, s1.##member10, #member10) \
  && serialize(strm, context, s1.##member11, #member11) \
  && serialize(strm, context, s1.##member12, #member12) \
  && serialize(strm, context, s1.##member13, #member13) \
  && serialize(strm, context, s1.##member14, #member14) \
  && serialize(strm, context, s1.##member15, #member15) \
  && serialize(strm, context, s1.##member16, #member16) \
  && serialize(strm, context, s1.##member17, #member17) \
  && serialize(strm, context, s1.##member18, #member18) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize(strm, context, s1.##member0, #member0) \
  && deserialize(strm, context, s1.##member1, #member1) \
  && deserialize(strm, context, s1.##member2, #member2) \
  && deserialize(strm, context, s1.##member3, #member3) \
  && deserialize(strm, context, s1.##member4, #member4) \
  && deserialize(strm, context, s1.##member5, #member5) \
  && deserialize(strm, context, s1.##member6, #member6) \
  && deserialize(strm, context, s1.##member7, #member7) \
  && deserialize(strm, context, s1.##member8, #member8) \
  && deserialize(strm, context, s1.##member9, #member9) \
  && deserialize(strm, context, s1.##member10, #member10) \
  && deserialize(strm, context, s1.##member11, #member11) \
  && deserialize(strm, context, s1.##member12, #member12) \
  && deserialize(strm, context, s1.##member13, #member13) \
  && deserialize(strm, context, s1.##member14, #member14) \
  && deserialize(strm, context, s1.##member15, #member15) \
  && deserialize(strm, context, s1.##member16, #member16) \
  && deserialize(strm, context, s1.##member17, #member17) \
  && deserialize(strm, context, s1.##member18, #member18) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

#define register_class_v2( object, member0, member_type0, member1, member_type1, member2, member_type2, member3, member_type3, member4, member_type4, member5, member_type5, member6, member_type6, member7, member_type7, member8, member_type8, member9, member_type9, member10, member_type10, member11, member_type11, member12, member_type12, member13, member_type13, member14, member_type14, member15, member_type15, member16, member_type16, member17, member_type17, member18, member_type18 ) \
inline bool serialize_##object(serialize_writer& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && serialize_##member_type0(strm, context, s1.##member0, #member0) \
  && serialize_##member_type1(strm, context, s1.##member1, #member1) \
  && serialize_##member_type2(strm, context, s1.##member2, #member2) \
  && serialize_##member_type3(strm, context, s1.##member3, #member3) \
  && serialize_##member_type4(strm, context, s1.##member4, #member4) \
  && serialize_##member_type5(strm, context, s1.##member5, #member5) \
  && serialize_##member_type6(strm, context, s1.##member6, #member6) \
  && serialize_##member_type7(strm, context, s1.##member7, #member7) \
  && serialize_##member_type8(strm, context, s1.##member8, #member8) \
  && serialize_##member_type9(strm, context, s1.##member9, #member9) \
  && serialize_##member_type10(strm, context, s1.##member10, #member10) \
  && serialize_##member_type11(strm, context, s1.##member11, #member11) \
  && serialize_##member_type12(strm, context, s1.##member12, #member12) \
  && serialize_##member_type13(strm, context, s1.##member13, #member13) \
  && serialize_##member_type14(strm, context, s1.##member14, #member14) \
  && serialize_##member_type15(strm, context, s1.##member15, #member15) \
  && serialize_##member_type16(strm, context, s1.##member16, #member16) \
  && serialize_##member_type17(strm, context, s1.##member17, #member17) \
  && serialize_##member_type18(strm, context, s1.##member18, #member18) \
  && strm.close( context); } \
inline bool serialize(serialize_writer& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return serialize_##object(strm, context, s1, name);} \
inline bool deserialize_##object(serialize_reader& strm, serialize_context& context, object & s1, const tchar* name=0) \
{ return strm.open( context, #object, name) \
  && deserialize_##member_type0(strm, context, s1.##member0, #member0) \
  && deserialize_##member_type1(strm, context, s1.##member1, #member1) \
  && deserialize_##member_type2(strm, context, s1.##member2, #member2) \
  && deserialize_##member_type3(strm, context, s1.##member3, #member3) \
  && deserialize_##member_type4(strm, context, s1.##member4, #member4) \
  && deserialize_##member_type5(strm, context, s1.##member5, #member5) \
  && deserialize_##member_type6(strm, context, s1.##member6, #member6) \
  && deserialize_##member_type7(strm, context, s1.##member7, #member7) \
  && deserialize_##member_type8(strm, context, s1.##member8, #member8) \
  && deserialize_##member_type9(strm, context, s1.##member9, #member9) \
  && deserialize_##member_type10(strm, context, s1.##member10, #member10) \
  && deserialize_##member_type11(strm, context, s1.##member11, #member11) \
  && deserialize_##member_type12(strm, context, s1.##member12, #member12) \
  && deserialize_##member_type13(strm, context, s1.##member13, #member13) \
  && deserialize_##member_type14(strm, context, s1.##member14, #member14) \
  && deserialize_##member_type15(strm, context, s1.##member15, #member15) \
  && deserialize_##member_type16(strm, context, s1.##member16, #member16) \
  && deserialize_##member_type17(strm, context, s1.##member17, #member17) \
  && deserialize_##member_type18(strm, context, s1.##member18, #member18) \
  && strm.close(context); } \
inline bool deserialize(serialize_reader& strm, serialize_context& context, const object & s1, const tchar* name=0) \
{ return deserialize_##object(strm, context, s1, name);}

