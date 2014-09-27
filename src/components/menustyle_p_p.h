/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "menustyle_p.h"
#include "boxstyle_p_p.h"

class MenuStylePrivate : public BoxStylePrivate
{

public:
    MenuStylePrivate(MenuStyle *parent);
    
    virtual QString indicatorBody() const;
    virtual QString itemBody() const;
    virtual QString leftArrowBody() const;
    virtual QString rightArrowBody() const;
    virtual QString scrollerBody() const;
    virtual QString separatorBody() const;
    virtual QString tearoffBody() const;
    
    Style *indicator;
    Style *item;
    Style *leftArrow;
    Style *rightArrow;
    Style *scroller;
    Style *separator;
    Style *tearoff;
    
    Q_DECLARE_PUBLIC(MenuStyle)
};

