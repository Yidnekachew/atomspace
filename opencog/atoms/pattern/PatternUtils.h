/**
 * PatternUtils.h
 *
 * Utilities for mangling graphs
 *
 * Copyright (C) 2009, 2014 Linas Vepstas <linasvepstas@gmail.com>
 * All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Created by Linas Vepstas February 2008
 */

#ifndef _OPENCOG_PATTERN_UTILS_H
#define _OPENCOG_PATTERN_UTILS_H

#include <set>
#include <vector>

#include <opencog/atoms/base/Handle.h>
#include <opencog/atoms/base/types.h>

namespace opencog {


// Make sure that variables can be found in the clauses.
// See C file for description
bool remove_constants(const HandleSet& vars,
                      HandleSeq& clauses,
                      HandleSeq& constants,
                      HandleSeqSeq &components,
                      HandleSeq &mandatory_clauses,
                      HandleSeq &cnf_clauses,
                      const AtomSpace &queried_as);

// check whether an Atom exists in a given atomspace.
bool is_in_atomspace(const Handle& handle, const AtomSpace& atomspace);

// Return true if the clause is constant
bool is_constant(const HandleSet& vars, const Handle& clause);

// See C file for description
void get_connected_components(const HandleSet& vars,
                              const HandleSeq& clauses,
                              HandleSeqSeq& compset,
                              std::vector<HandleSet>& compvars);

} // namespace opencog

#endif // _OPENCOG_PATTERN_UTILS_H
