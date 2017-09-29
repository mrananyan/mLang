/*
$Author = Sargis Ananyan;
$Corp = RedM Inc;
$Web = https://redm.pro/;
$Lincese = BSD 3;
$Name = mLang;
$Description = A programming language for web programming.;
*/

#pragma once
#include "operation.h"
#include "graph.h"
/** used pointers to **/
class TypeInf;

class VarData;
class ClassData;
class DefineData;
class FunctionData;
class SrcFile;
class Token;
class FunctionSet;
class FunctionMatcher;
struct Location;

typedef Id <FunctionData> FunctionPtr;
typedef Id <VarData> VarPtr;
typedef Id <ClassData> ClassPtr;
typedef Id <DefineData> DefinePtr;
typedef Id <SrcFile> SrcFilePtr;
typedef Id <FunctionSet> FunctionSetPtr;
typedef Id <TypeInf> TypeInfPtr;

template <Operation Op>
class vertex_inner;


//TODO: use private and protected when necessary
template <Operation Op>
class VertexAdaptor {
public:
  vertex_inner <Op> *impl;

  VertexAdaptor() : impl (NULL) {
  }

  explicit VertexAdaptor (vertex_inner <Op> *impl) : impl (impl) {
  }

  //TODO: use dynamic cast to enforce correctnes
  template <Operation FromOp>
  VertexAdaptor (const VertexAdaptor <FromOp> &from) : impl (dynamic_cast <vertex_inner <Op> *> (from.impl)) {
    dl_assert (impl != NULL, "???");
  }

  template <Operation FromOp>
  VertexAdaptor &operator = (const VertexAdaptor <FromOp> &from) {
    impl = (vertex_inner <Op> *)from.impl;
    return *this;
  }

  inline bool is_null() const {
    return impl == NULL;
  }
  inline bool not_null() const {
    return !is_null();
  }
  vertex_inner <Op> *operator ->() {
    assert (impl != NULL);
    return impl;
  }
  const vertex_inner <Op> *operator ->() const {
    assert (impl != NULL);
    return impl;
  }

  vertex_inner <Op> &operator *() {
    assert (impl != NULL);
    return *impl;
  }
  const vertex_inner <Op> &operator *() const {
    assert (impl != NULL);
    return *impl;
  }
  template <Operation to> VertexAdaptor <to> as() {
    return *this;
  }

  static void init_properties (OpProperties *x) {
    vertex_inner <Op>::init_properties (x);
  }
};

typedef VertexAdaptor <meta_op_base> VertexPtr;
