# Binding

<a id="s_binding"></a>
```
typedef struct binding {
        const char *name;
        const char **value;
} s_binding
```

Binding of a variable named **name** with its constant string
value pointed to by **value**.

Multiple bindings can be given in a NULL terminated array, that
is the last element of the array will have a NULL name and a NULL
value pointer.

---

<a id="bindings_get"></a>
`const char ** bindings_get (s_binding *bindings, const char *name)`

Get a binding named **name** from **bindings**.

---

<a id="bindings_get_or_die"></a>
`const char ** bindings_get_or_die (s_binding *bindings, const char *name)`

Get a binding named **name** from **bindings** or exit program with error status.

---

<a id="bindings_nullify"></a>
`void bindings_nullify (s_binding *bindings)`

Set all bindings values to NULL.
