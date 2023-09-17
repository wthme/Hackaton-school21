<?php

declare(strict_types=1);
 
namespace App\Controller;
 
use League\Flysystem\FilesystemException;
use League\Flysystem\FilesystemOperator;
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
    #[Route('/content', name: 'content', methods:['get'] )]
    public function contentAction(FilesystemOperator $defaultStorage): JsonResponse
    {
        try {
            $listing = $defaultStorage->listContents('./', true);
        
            /** @var \League\Flysystem\StorageAttributes $item */
            $content = [
                'files' => [],
                'events' => [],
            ];
            foreach ($listing as $item) {
                $path = $item->path();
        
                if ($item instanceof \League\Flysystem\FileAttributes) {
                    // handle the file
                    $content['files'][] = $item->path();
                } elseif ($item instanceof \League\Flysystem\DirectoryAttributes) {
                    // handle the directory
                    $content['events'][] = $item->path();
                }
            }
        } catch (FilesystemException $exception) {
            // handle the error
        }

        return $this->json($content);
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
                $file->move('./uploaded', $file->getClientOriginalName());
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