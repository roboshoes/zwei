#include "Context.h"

using ContextRef = zwei::Context&;
using Context = zwei::Context;
using Command = zwei::Command;
using vectorf = std::vector<float>;

void Context::apply() const {

    for ( auto it = commands.begin(); it != commands.end(); ++it ) {
        const std::vector<float>& argsRef = it->getArguments();

        switch ( it->getName() ) {
            case Command::DRAW_LINE:
                cinder::gl::drawLine( cinder::vec2( argsRef[ 0 ], argsRef[ 1 ] ), cinder::vec2( argsRef[ 2 ], argsRef[ 3 ] ) );
                break;
            case Command::DRAW_RECT:
                cinder::gl::drawSolidRect( cinder::Rectf( argsRef[ 0 ], argsRef[ 1 ], argsRef[ 2 ], argsRef[ 3 ] ) );
                break;
            case Command::DRAW_CIRCLE:
                cinder::gl::drawSolidCircle(cinder::vec2( argsRef[ 0 ], argsRef[ 1 ] ), argsRef[ 2 ] );
                break;
            case Command::SET_COLOR:
                cinder::gl::color( cinder::Color( argsRef[ 0 ], argsRef[ 1 ], argsRef[ 2 ] ) );
                break;
        }
    }
}

ContextRef Context::setColor( cinder::Color color ) {

    commands.push_back( Command( Command::SET_COLOR, vectorf{ color.r, color.g, color.b } ) );

    return *this;
}

ContextRef Context::drawLine( cinder::vec2 start, cinder::vec2 end ) {

    commands.push_back( Command( Command::DRAW_LINE, vectorf{ start.x, start.y, end.x, end.y } ) );

    boundingBox += zwei::BoundingBox::makeFromPoints( start, end );

    return *this;
}

ContextRef Context::drawRect( cinder::vec2 position, cinder::vec2 size ) {

    commands.push_back( Command( Command::DRAW_RECT, vectorf{ position.x, position.y, size.x, size.y } ) );

    boundingBox += zwei::BoundingBox( position, size );

    return *this;
}

ContextRef Context::drawCircle( cinder::vec2 center, float radius ) {

    commands.push_back( Command( Command::DRAW_CIRCLE, vectorf{ center.x, center.y, radius } ) );

    boundingBox += zwei::BoundingBox( center - radius, cinder::vec2( radius * 2 ) );

    return *this;
}