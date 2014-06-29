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

#ifndef IMAGE_P_P_H
#define IMAGE_P_P_H

#include "image_p.h"
#include "imagebase_p_p.h"

class ImagePrivate : public ImageBasePrivate
{

public:
    ImagePrivate(Image *parent);

    void load();

    void _q_onLoaderFinished(ImageLoader *loader);
    void _q_onLoaderCanceled(ImageLoader *loader);
    void _q_onLoaderProgressChanged(qreal p);

    Image::FillMode fillMode;

    Q_DECLARE_PUBLIC(Image)
};

#endif // IMAGE_P_P_H
