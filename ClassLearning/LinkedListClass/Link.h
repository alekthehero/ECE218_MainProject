#pragma once

template <typename any>
struct link
{
    any * data;
    link * next;

    link(any * data, link * next = nullptr): data(data), next(next) {}
};
