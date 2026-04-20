"use client"

import { useEffect } from "react"
import { useRouter } from "next/navigation"

export default function HomePage() {
  const router = useRouter()

  useEffect(() => {
    router.replace("/landing")
  }, [router])

  return <main className="min-h-screen bg-background" />
}
