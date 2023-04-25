

PyTypeObject Random_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "_random.Random",                   /*tp_name*/
    sizeof(RandomObject),               /*tp_basicsize*/
    0,                                  /*tp_itemsize*/
    /* methods */
    0,                                  /*tp_dealloc*/
    0,                                  /*tp_print*/
    0,                                  /*tp_getattr*/
    0,                                  /*tp_setattr*/
    0,                                  /*tp_compare*/
    0,                                  /*tp_repr*/
    0,                                  /*tp_as_number*/
    0,                                  /*tp_as_sequence*/
    0,                                  /*tp_as_mapping*/
    0,                                  /*tp_hash*/
    0,                                  /*tp_call*/
    0,                                  /*tp_str*/
    PyObject_GenericGetAttr,            /*tp_getattro*/
    0,                                  /*tp_setattro*/
    0,                                  /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,           /*tp_flags*/
    random_doc,                         /*tp_doc*/
    0,                                  /*tp_traverse*/
    0,                                  /*tp_clear*/
    0,                                  /*tp_richcompare*/
    0,                                  /*tp_weaklistoffset*/
    0,                                  /*tp_iter*/
    0,                                  /*tp_iternext*/
    random_methods,                     /*tp_methods*/
    0,                                  /*tp_members*/
    0,                                  /*tp_getset*/
    0,                                  /*tp_base*/
    0,                                  /*tp_dict*/
    0,                                  /*tp_descr_get*/
    0,                                  /*tp_descr_set*/
    0,                                  /*tp_dictoffset*/
    0,                                  /*tp_init*/
    0,                                  /*tp_alloc*/
    random_new,                         /*tp_new*/
    _PyObject_Del,                      /*tp_free*/
    0,                                  /*tp_is_gc*/
};

PyDoc_STRVAR(module_doc,
"Module implements the Mersenne Twister random number generator.");

PyMODINIT_FUNC
init_random(void)
{
    PyObject *m;

    if (PyType_Ready(&Random_Type) < 0)
        return;
    m = Py_InitModule3("_random", NULL, module_doc);
    if (m == NULL)
        return;
    Py_INCREF(&Random_Type);
    PyModule_AddObject(m, "Random", (PyObject *)&Random_Type);
}