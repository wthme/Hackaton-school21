<?php

declare(strict_types=1);

namespace App\Model;

class ErrorDebugDetails
{
    public function __construct(private readonly string $trace)
    {
    }

    public function getTrace(): string
    {
        return $this->trace;
    }
}