/***************************************************************************\
*                                                                           *
*  BitlBee - An IRC to IM gateway                                           *
*  Base64 handling functions. encode_real() is mostly based on the y64 en-  *
*  coder from libyahoo2. Moving it to a new file because it's getting big.  *
*                                                                           *
*  Copyright 2006 Wilmer van der Gaast <wilmer@gaast.net>                   *
*                                                                           *
*  This program is free software; you can redistribute it and/or modify     *
*  it under the terms of the GNU General Public License as published by     *
*  the Free Software Foundation; either version 2 of the License, or        *
*  (at your option) any later version.                                      *
*                                                                           *
*  This program is distributed in the hope that it will be useful,          *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
*  GNU General Public License for more details.                             *
*                                                                           *
*  You should have received a copy of the GNU General Public License along  *
*  with this program; if not, write to the Free Software Foundation, Inc.,  *
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
*                                                                           *
\***************************************************************************/

#include <glib.h>
#include <string.h>
#include "base64.h"

char *tobase64(const char *text)
{
	return base64_encode((const unsigned char *)text, strlen(text));
}

char *base64_encode(const unsigned char *in, int len)
{
	return g_base64_encode(in, len);
}

/* Just a simple wrapper, but usually not very convenient because of zero
   termination. */
char *frombase64(const char *in)
{
	unsigned char *out;
	base64_decode(in, &out);
	return (char*) out;
}

int base64_decode(const char *in, unsigned char **out)
{
	gsize len;
	*out = g_base64_decode(in, &len);

	/* Some silly functions expect it to be zero terminated */
	*out = g_realloc(*out, len + 1);
	out[0][len] = 0;

	return len;
}
