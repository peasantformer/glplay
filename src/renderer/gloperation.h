#ifndef GLOPERATION_H
#define GLOPERATION_H

class Renderer;

struct GLOperation
{
    virtual ~GLOperation();
    virtual void visit(Renderer & renderer) = 0;
};

#endif // GLOPERATION_H
