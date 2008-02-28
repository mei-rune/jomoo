#ifndef MAP_UNIQUE_ITERATOR_H
#define MAP_UNIQUE_ITERATOR_H

#include "config.h"

#if !defined (Hazel_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* Hazel_LACKS_PRAGMA_ONCE */

// Include files
#include "config_PluginManager.h"
# include <iterator>

_seal_begin

template <class Map>
class MapUniqueIterator ITERATOR_BASE(bidirectional_iterator,
				      typename Map::mapped_type,
				      typename Map::difference_type)
{
public:
    typedef std::bidirectional_iterator_tag	iterator_category;
    typedef typename Map::const_iterator	base_iterator;
    typedef typename Map::key_type		key_type;
    typedef typename Map::mapped_type		value_type;
    typedef typename Map::difference_type	difference_type;
    typedef const value_type &			reference;
    typedef const value_type *			pointer;

    MapUniqueIterator (void);
    MapUniqueIterator (base_iterator pos, const Map *map);


    bool		operator== (const MapUniqueIterator &x) const;
    bool		operator!= (const MapUniqueIterator &x) const;
    reference		operator* (void) const;
    pointer		operator-> (void) const;
    MapUniqueIterator &operator++ (void);
    MapUniqueIterator	operator++ (int);
    MapUniqueIterator &operator-- (void);
    MapUniqueIterator	operator-- (int);

 private:
    base_iterator	m_pos;
    const Map		*m_map;
};

template <class Map>
inline
MapUniqueIterator<Map>::MapUniqueIterator (void)
{}

template <class Map>
inline
MapUniqueIterator<Map>::MapUniqueIterator (base_iterator pos, const Map *map)
    : m_pos (pos),
      m_map (map)
{}

template <class Map>
inline bool
MapUniqueIterator<Map>::operator== (const MapUniqueIterator &x) const
{ return m_pos == x.m_pos; }

template <class Map>
inline bool
MapUniqueIterator<Map>::operator!= (const MapUniqueIterator &x) const
{ return m_pos != x.m_pos; }

template <class Map>
inline typename MapUniqueIterator<Map>::reference
MapUniqueIterator<Map>::operator* (void) const
{ return m_pos->second; }

template <class Map>
inline typename MapUniqueIterator<Map>::pointer
MapUniqueIterator<Map>::operator-> (void) const
{ return &m_pos->second; }

template <class Map>
inline MapUniqueIterator<Map> &
MapUniqueIterator<Map>::operator++ (void)
{
    const key_type &current = m_pos->first;
    while (m_pos != m_map->end () && m_pos->first == current)
	++m_pos;
    return *this;
}

template <class Map>
inline MapUniqueIterator<Map>
MapUniqueIterator<Map>::operator++ (int)
{ MapUniqueIterator tmp (*this); ++*this; return tmp; }

template <class Map>
inline MapUniqueIterator<Map> &
MapUniqueIterator<Map>::operator-- (void)
{
    const key_type &current = m_pos->first;
    while (m_pos != m_map->begin () && m_pos->first == current)
	--m_pos;
    return *this;
}

template <class Map>
inline MapUniqueIterator<Map>
MapUniqueIterator<Map>::operator-- (int)
{ MapUniqueIterator tmp (*this); --*this; return tmp; }

_seal_end

#endif // MAP_UNIQUE_ITERATOR_H
