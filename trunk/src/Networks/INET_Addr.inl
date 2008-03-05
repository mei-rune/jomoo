

JOMOO_INLINE
JOMOO_INET_Addr::~JOMOO_INET_Addr (void)
{
}

JOMOO_INLINE void
JOMOO_INET_Addr::reset (void)
{
  memset (&this->m_addr_ , 0, sizeof (this->m_addr_ ));
  this->m_addr_.sa_family = AF_INET;
}
