# -*- coding: utf-8 -*-
# versionbase.py
# 
# Copyright (c) 2010-2012 BAM
# Federal Institute for Materials Research and Testing
# Division I.3 Structure Analysis; Polymer Analysis
# Richard-Willstaetter-Strasse 11, 12489 Berlin, Germany
# 
# This file is part of cutesnake.
#
# cutesnake is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# cutesnake is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with cutesnake.  If not, see <http://www.gnu.org/licenses/>.
# 
# Author(s) of this file:
# Ingo Bressler (cutesnake@ingobressler.net)

class VersionBase(object):
    _name = None
    _number = None
    _organizationName = None
    _organizationDomain = None
    _defaultSettings = None

    @classmethod
    def name(cls):
        return cls._name

    @classmethod
    def number(cls):
        # pywin32 has a problem with version nr like "20111110"
        return cls._number

    @classmethod
    def organizationName(cls):
        return cls._organizationName

    @classmethod
    def organizationDomain(cls):
        return cls._organizationDomain

    @classmethod
    def defaultSettings(cls):
        return cls._defaultSettings

    @classmethod
    def isDefined(cls):
        return (type(cls.name()) is str and
                type(cls.number()) is str and
                type(cls.organizationName()) is str)

    @classmethod
    def isValid(cls, other):
        return (issubclass(other, cls) and other.isDefined())

# vim: set ts=4 sw=4 sts=4 tw=0:
