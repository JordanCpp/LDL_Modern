// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

import Graphics;

int main()
{
    auto canvasResource = Graphics::CanvasNew(800, 600);

    if (!canvasResource)
    {
        return -1;
    }

    auto& canvas = *canvasResource;

    while (canvas->GetEvent())
    {
    }

    return 0;
}
