HAZEL_INLINE
hazel_sap::~hazel_sap (void)
{
}

HAZEL_INLINE hazel_sap_HANDLE
hazel_sap::get_handle (void) const
{
  return this->handle_;
}


HAZEL_INLINE void
hazel_sap::set_handle (hazel_sap_HANDLE handle)
{
  this->handle_ = handle;
}

HAZEL_INLINE void
hazel_sap::swap( hazel_sap& r )
{
	std::swap( this->handle_, r.handle_ );
}

//HAZEL_INLINE int 
//hazel_sap::control (int cmd, void *arg) const
//{
//  return ::ioctlsocket (this->handle_, cmd, arg);
//}

HAZEL_INLINE int 
hazel_sap::set_option (int level, 
		      int option, 
		      void *optval, 
		      int optlen) const
{
  return setsockopt (this->get_handle (), level, 
			     option, (char *) optval, optlen);
}

HAZEL_INLINE int 
hazel_sap::get_option (int level, 
		      int option, 
		      void *optval, 
		      int *optlen) const
{
  return getsockopt (this->get_handle (), level, 
			     option, (char *) optval, optlen);
}