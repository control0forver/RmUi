#pragma once

namespace RmUi::Infrastructure
{
    class IClassStructor
    {
    public:
        virtual ~IClassStructor() = default;

        virtual void _reset() = 0;
    };
    
} // namespace RmUi::Infrastructure
