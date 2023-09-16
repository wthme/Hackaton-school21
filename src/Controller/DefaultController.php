<?php
 
namespace App\Controller;
 
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\JsonResponse;
use Symfony\Component\Routing\Annotation\Route;
// use Doctrine\Persistence\ManagerRegistry;
use Symfony\Component\HttpFoundation\Request;
use App\Entity\Project;
 
#[Route('/api', name: 'api_')]
class DefaultController extends AbstractController
{
    #[Route('/projects', name: 'project_index', methods:['get'] )]
    public function index(): JsonResponse
    {
        // $products = $doctrine
        //     ->getRepository(Project::class)
        //     ->findAll();
   
        // $data = [];
   
        // foreach ($products as $product) {
           $data[] = [
            //    'id' => $product->getId(),
               'name' => 'test',
            //    'description' => $product->getDescription(),
           ];
        // } 
        
   
        return $this->json($data);
    }
}