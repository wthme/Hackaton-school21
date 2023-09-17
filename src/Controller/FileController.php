<?php

declare(strict_types=1);
 
namespace App\Controller;
 
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\BinaryFileResponse;
use Symfony\Component\HttpFoundation\File\Exception\FileException;
use Symfony\Component\HttpFoundation\File\File;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Routing\Annotation\Route;
 
#[Route('/api/v1', name: 'api_')]
class FileController extends AbstractController
{
    #[Route('/file', name: 'file_get', methods:['get'] )]
    public function fileAction(): BinaryFileResponse
    {
        // load the file from the filesystem
        $file = new File('./files/30f5145s-960.jpg');

        return $this->file($file);
    }

    #[Route('/upload', name: 'file_upload', methods:['post'] )]
    public function uploadAction(Request $request): JsonResponse
    {
        if (!$request->files) {
            return $this->json([
                'status' => 'error',
                'message' => 'Files missing',
            ]);
        }

        try {
            foreach($request->files as $file) {
                $file->move('./files', $file->getClientOriginalName());
            }
            return $this->json([
                'status' => 'success',
                'message' => 'Files uploaded successfully',
            ]);
        } catch (FileException $e) {
            return $this->json([
                'status' => 'error',
                'message' => $e->getMessage(),
            ]);
        }
    }
}