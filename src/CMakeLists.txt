add_library(${PROJECT_NAME} STATIC
        header.c ../include/header.h
        question.c ../include/question.h
        message.c ../include/message.h
        resource_record.c ../include/resource_record.h

        a.c ../include/a.h
        aaaa.c ../include/aaaa.h
        cname.c ../include/cname.h)
