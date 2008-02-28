

Hazel_INLINE
Hazel_INET_Addr::~Hazel_INET_Addr (void)
{
}

Hazel_INLINE void
Hazel_INET_Addr::reset (void)
{
  memset (&this->m_addr_ , 0, sizeof (this->m_addr_ ));
  this->m_addr_.sa_family = AF_INET;
}
