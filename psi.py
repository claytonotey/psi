# This file was automatically generated by SWIG (http://www.swig.org).
# Version 4.0.2
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info < (2, 7, 0):
    raise RuntimeError("Python 2.7 or later required")

# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _psi
else:
    import _psi

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "thisown":
            self.this.own(value)
        elif name == "this":
            set(self, name, value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


class SwigPyIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _psi.delete_SwigPyIterator

    def value(self):
        return _psi.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _psi.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _psi.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _psi.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _psi.SwigPyIterator_equal(self, x)

    def copy(self):
        return _psi.SwigPyIterator_copy(self)

    def next(self):
        return _psi.SwigPyIterator_next(self)

    def __next__(self):
        return _psi.SwigPyIterator___next__(self)

    def previous(self):
        return _psi.SwigPyIterator_previous(self)

    def advance(self, n):
        return _psi.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _psi.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _psi.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _psi.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _psi.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _psi.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _psi.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self

# Register SwigPyIterator in _psi:
_psi.SwigPyIterator_swigregister(SwigPyIterator)

class vectorD(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def iterator(self):
        return _psi.vectorD_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _psi.vectorD___nonzero__(self)

    def __bool__(self):
        return _psi.vectorD___bool__(self)

    def __len__(self):
        return _psi.vectorD___len__(self)

    def __getslice__(self, i, j):
        return _psi.vectorD___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _psi.vectorD___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _psi.vectorD___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _psi.vectorD___delitem__(self, *args)

    def __getitem__(self, *args):
        return _psi.vectorD___getitem__(self, *args)

    def __setitem__(self, *args):
        return _psi.vectorD___setitem__(self, *args)

    def pop(self):
        return _psi.vectorD_pop(self)

    def append(self, x):
        return _psi.vectorD_append(self, x)

    def empty(self):
        return _psi.vectorD_empty(self)

    def size(self):
        return _psi.vectorD_size(self)

    def swap(self, v):
        return _psi.vectorD_swap(self, v)

    def begin(self):
        return _psi.vectorD_begin(self)

    def end(self):
        return _psi.vectorD_end(self)

    def rbegin(self):
        return _psi.vectorD_rbegin(self)

    def rend(self):
        return _psi.vectorD_rend(self)

    def clear(self):
        return _psi.vectorD_clear(self)

    def get_allocator(self):
        return _psi.vectorD_get_allocator(self)

    def pop_back(self):
        return _psi.vectorD_pop_back(self)

    def erase(self, *args):
        return _psi.vectorD_erase(self, *args)

    def __init__(self, *args):
        _psi.vectorD_swiginit(self, _psi.new_vectorD(*args))

    def push_back(self, x):
        return _psi.vectorD_push_back(self, x)

    def front(self):
        return _psi.vectorD_front(self)

    def back(self):
        return _psi.vectorD_back(self)

    def assign(self, n, x):
        return _psi.vectorD_assign(self, n, x)

    def resize(self, *args):
        return _psi.vectorD_resize(self, *args)

    def insert(self, *args):
        return _psi.vectorD_insert(self, *args)

    def reserve(self, n):
        return _psi.vectorD_reserve(self, n)

    def capacity(self):
        return _psi.vectorD_capacity(self)
    __swig_destroy__ = _psi.delete_vectorD

# Register vectorD in _psi:
_psi.vectorD_swigregister(vectorD)

class vectorVD(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def iterator(self):
        return _psi.vectorVD_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _psi.vectorVD___nonzero__(self)

    def __bool__(self):
        return _psi.vectorVD___bool__(self)

    def __len__(self):
        return _psi.vectorVD___len__(self)

    def __getslice__(self, i, j):
        return _psi.vectorVD___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _psi.vectorVD___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _psi.vectorVD___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _psi.vectorVD___delitem__(self, *args)

    def __getitem__(self, *args):
        return _psi.vectorVD___getitem__(self, *args)

    def __setitem__(self, *args):
        return _psi.vectorVD___setitem__(self, *args)

    def pop(self):
        return _psi.vectorVD_pop(self)

    def append(self, x):
        return _psi.vectorVD_append(self, x)

    def empty(self):
        return _psi.vectorVD_empty(self)

    def size(self):
        return _psi.vectorVD_size(self)

    def swap(self, v):
        return _psi.vectorVD_swap(self, v)

    def begin(self):
        return _psi.vectorVD_begin(self)

    def end(self):
        return _psi.vectorVD_end(self)

    def rbegin(self):
        return _psi.vectorVD_rbegin(self)

    def rend(self):
        return _psi.vectorVD_rend(self)

    def clear(self):
        return _psi.vectorVD_clear(self)

    def get_allocator(self):
        return _psi.vectorVD_get_allocator(self)

    def pop_back(self):
        return _psi.vectorVD_pop_back(self)

    def erase(self, *args):
        return _psi.vectorVD_erase(self, *args)

    def __init__(self, *args):
        _psi.vectorVD_swiginit(self, _psi.new_vectorVD(*args))

    def push_back(self, x):
        return _psi.vectorVD_push_back(self, x)

    def front(self):
        return _psi.vectorVD_front(self)

    def back(self):
        return _psi.vectorVD_back(self)

    def assign(self, n, x):
        return _psi.vectorVD_assign(self, n, x)

    def resize(self, *args):
        return _psi.vectorVD_resize(self, *args)

    def insert(self, *args):
        return _psi.vectorVD_insert(self, *args)

    def reserve(self, n):
        return _psi.vectorVD_reserve(self, n)

    def capacity(self):
        return _psi.vectorVD_capacity(self)
    __swig_destroy__ = _psi.delete_vectorVD

# Register vectorVD in _psi:
_psi.vectorVD_swigregister(vectorVD)

class vectorVVD(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr

    def iterator(self):
        return _psi.vectorVVD_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _psi.vectorVVD___nonzero__(self)

    def __bool__(self):
        return _psi.vectorVVD___bool__(self)

    def __len__(self):
        return _psi.vectorVVD___len__(self)

    def __getslice__(self, i, j):
        return _psi.vectorVVD___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _psi.vectorVVD___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _psi.vectorVVD___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _psi.vectorVVD___delitem__(self, *args)

    def __getitem__(self, *args):
        return _psi.vectorVVD___getitem__(self, *args)

    def __setitem__(self, *args):
        return _psi.vectorVVD___setitem__(self, *args)

    def pop(self):
        return _psi.vectorVVD_pop(self)

    def append(self, x):
        return _psi.vectorVVD_append(self, x)

    def empty(self):
        return _psi.vectorVVD_empty(self)

    def size(self):
        return _psi.vectorVVD_size(self)

    def swap(self, v):
        return _psi.vectorVVD_swap(self, v)

    def begin(self):
        return _psi.vectorVVD_begin(self)

    def end(self):
        return _psi.vectorVVD_end(self)

    def rbegin(self):
        return _psi.vectorVVD_rbegin(self)

    def rend(self):
        return _psi.vectorVVD_rend(self)

    def clear(self):
        return _psi.vectorVVD_clear(self)

    def get_allocator(self):
        return _psi.vectorVVD_get_allocator(self)

    def pop_back(self):
        return _psi.vectorVVD_pop_back(self)

    def erase(self, *args):
        return _psi.vectorVVD_erase(self, *args)

    def __init__(self, *args):
        _psi.vectorVVD_swiginit(self, _psi.new_vectorVVD(*args))

    def push_back(self, x):
        return _psi.vectorVVD_push_back(self, x)

    def front(self):
        return _psi.vectorVVD_front(self)

    def back(self):
        return _psi.vectorVVD_back(self)

    def assign(self, n, x):
        return _psi.vectorVVD_assign(self, n, x)

    def resize(self, *args):
        return _psi.vectorVVD_resize(self, *args)

    def insert(self, *args):
        return _psi.vectorVVD_insert(self, *args)

    def reserve(self, n):
        return _psi.vectorVVD_reserve(self, n)

    def capacity(self):
        return _psi.vectorVVD_capacity(self)
    __swig_destroy__ = _psi.delete_vectorVVD

# Register vectorVVD in _psi:
_psi.vectorVVD_swigregister(vectorVVD)

ImageSize = _psi.ImageSize
ImageLeft = _psi.ImageLeft
ImageRight = _psi.ImageRight
MinPeak = _psi.MinPeak
MaxPeak = _psi.MaxPeak
NumMinima = _psi.NumMinima
NumMaxima = _psi.NumMaxima
NumExtrema = _psi.NumExtrema
class Frame(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    minima = property(_psi.Frame_minima_get, _psi.Frame_minima_set)
    maxima = property(_psi.Frame_maxima_get, _psi.Frame_maxima_set)
    condition = property(_psi.Frame_condition_get, _psi.Frame_condition_set)
    time = property(_psi.Frame_time_get, _psi.Frame_time_set)
    minFrame = property(_psi.Frame_minFrame_get, _psi.Frame_minFrame_set)
    fv0 = property(_psi.Frame_fv0_get, _psi.Frame_fv0_set)
    fv = property(_psi.Frame_fv_get, _psi.Frame_fv_set)

    def getVisibility(self, fringe, absmin, offset):
        return _psi.Frame_getVisibility(self, fringe, absmin, offset)

    def __init__(self, extrema, condition, time):
        _psi.Frame_swiginit(self, _psi.new_Frame(extrema, condition, time))
    __swig_destroy__ = _psi.delete_Frame

# Register Frame in _psi:
_psi.Frame_swigregister(Frame)

class Session(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    bRobot = property(_psi.Session_bRobot_get, _psi.Session_bRobot_set)
    time = property(_psi.Session_time_get, _psi.Session_time_set)
    frames = property(_psi.Session_frames_get, _psi.Session_frames_set)
    conditionTimes = property(_psi.Session_conditionTimes_get, _psi.Session_conditionTimes_set)

    def __init__(self, bRobot, time, conditionTimes, nTimes):
        _psi.Session_swiginit(self, _psi.new_Session(bRobot, time, conditionTimes, nTimes))

    def getMin(self, absmin):
        return _psi.Session_getMin(self, absmin)

    def analyzePairs(self, lag, tau, dfvs):
        return _psi.Session_analyzePairs(self, lag, tau, dfvs)
    __swig_destroy__ = _psi.delete_Session

# Register Session in _psi:
_psi.Session_swigregister(Session)

class Sessions(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    sessions = property(_psi.Sessions_sessions_get, _psi.Sessions_sessions_set)

    def __init__(self, dirname):
        _psi.Sessions_swiginit(self, _psi.new_Sessions(dirname))

    def analyzeFringe(self, lag, tau, outlier):
        return _psi.Sessions_analyzeFringe(self, lag, tau, outlier)

    def getTrend(self):
        return _psi.Sessions_getTrend(self)

    def getVisibilities(self, fringe, absmin, bRandom, offset):
        return _psi.Sessions_getVisibilities(self, fringe, absmin, bRandom, offset)

    def removeOutliers(self, dfvs, outlierRatio):
        return _psi.Sessions_removeOutliers(self, dfvs, outlierRatio)
    __swig_destroy__ = _psi.delete_Sessions

# Register Sessions in _psi:
_psi.Sessions_swigregister(Sessions)



