#include "Playground.hpp"

Playground::Playground(Base &blueBase, Base &redBase) : m_blueBase(blueBase), m_redBase(redBase), m_field() {
    m_field.fill(nullptr);
}

Playground::Playground(const Playground &other) : m_blueBase(other.m_blueBase), m_redBase(other.m_redBase),
                                                  m_field(other.m_field) {}