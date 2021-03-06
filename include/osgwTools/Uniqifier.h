/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * osgWorks is (C) Copyright 2009-2012 by Kenneth Mark Bryden
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#ifndef __OSGWTOOLS_UNIQIFIER_H__
#define __OSGWTOOLS_UNIQIFIER_H__ 1

#include <osgwTools/Export.h>
#include <osgwTools/Version.h>
#include <osg/NodeVisitor>


namespace osgwTools
{


/** \defgroup uniqifiers Node Uniquification Tools
\brief Tools to eliminate shared nodes and multiparenting.

These tools make shallow copies of shared nodes, all shared nodes in a NodePath, and
all shared nodes in an entire scene graph. The shared nodes are replaced with the shallow
copies so that all nodes are unique, but data is still shared.

These tools are useful in cases where your scene graph makes use of node sharing,
but you need to perform a specific operation on just one of the shared instances,
and the decorator design pattern can't be used (for whatever reason). */
/*@{*/

    
/** \brief Uniquify a shared Node.

Remove \c child from \c parent's child list and replace it
with a shallow copy of \c child.
\return The address of the new shallow copy of \c child. */
OSGWTOOLS_EXPORT osg::Node* uniqify( osg::Node* child, osg::Group* parent );

/** \brief Uniquify a NodePath to eliminate all shared Nodes.

Starting with the second Node in \c np, iterate over \c np
and call uniquify(osg::Node*,osg::Group*) so that the entire
NodePath contains no multiparenting.

Because uniquify(osg::Node*,osg::Group*) creates shallow copies
with new addresses, \c np is invalid after this operation. Use
the return value instead.
\return A new NodePath that references the created nodes. */
OSGWTOOLS_EXPORT osg::NodePath uniqify( const osg::NodePath& np );

/** \class Uniqifier Uniqifier.h <osgwTools/Uniqifier.h>
\brief Eliminates multiparenting by turning shared nodes into unique nodes.

Note regarding Geometry and Drawable Handling

Around OSG v3.3.2, Geode was made to derive from Group, and Drawable made to
derive from Node, such that Geodes have Drawable children. osgWorks v3.00.02
treats Drawables as Node objects, which means the Uniqifier ensures that all
Drawables are made unique. Prior to osgWorks v3.00.02, Drawables are treated as
data rather than Node objects, which is just how OSG treated them prior to this
change. As a result, pre-v3.00.02 osgWorks does not create unique Drawables.
Drawables that are shared by multiple Geodes will remain shared after Uniqification.
*/
class OSGWTOOLS_EXPORT Uniqifier : public osg::NodeVisitor
{
public:
    Uniqifier( osg::NodeVisitor::TraversalMode mode=osg::NodeVisitor::TRAVERSE_ALL_CHILDREN );

    virtual void apply( osg::Node& node );
    virtual void apply( osg::Group& node );
#if( OSGWORKS_OSG_VERSION < 30302 )
    virtual void apply( osg::Geode& node );
#endif

protected:
};


/*@}*/


// osgwTools
}


// __OSGWTOOLS_UNIQIFIER_H__
#endif
