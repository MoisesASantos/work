import { redirect } from "next/navigation"

export default async function PharmacyDetailsPage({ params }: { params: Promise<{ id: string }> }) {
  const resolvedParams = await params
  redirect(`/instituicao/${resolvedParams.id}`)
}
